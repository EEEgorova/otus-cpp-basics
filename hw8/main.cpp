#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <mutex>

#include "CRC32.hpp"
#include "IO.hpp"

std::mutex myMutex;
bool resultReady = false;

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

void checkInRange(std::vector<char> &data,
                  uint32_t originalCrc32, 
                  size_t start,
                  size_t finish) {
 
  std::vector<char> result = data;
  for (size_t i = start; i <= finish; ++i) {
    if (resultReady) return;

    // Заменяем последние четыре байта на значение i
    replaceLastFourBytes(result, uint32_t(i));
    // Вычисляем CRC32 текущего вектора result
    auto currentCrc32 = crc32(result.data(), result.size());

    if (currentCrc32 == originalCrc32) {
      std::lock_guard<std::mutex> guard(myMutex);
      std::cout << "Success\n";
      resultReady = true;
      data = result;
      return;
    }
    
  }
  return;
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
   * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */
  const size_t maxVal = std::numeric_limits<uint32_t>::max();
  std::vector<std::thread> threads;
  size_t threadsSize = 4;
  threads.resize(threadsSize);

  for (size_t i = 0; i < threadsSize; ++i) {
      size_t start = maxVal / threadsSize * i;
      size_t finish = (i == threadsSize - 1) ? maxVal: maxVal / threadsSize * (i + 1);
      threads[i] = std::thread(checkInRange, result, originalCrc32, start, finish);
  }
  for ( auto & t : threads) {
    t.join();
  }
  
  if (resultReady) return result;

  throw std::logic_error("Can't hack");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
