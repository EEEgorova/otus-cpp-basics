// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void run_count_words( char * fname, Counter * result, int * codeResult);

void count_words(std::istream& stream, Counter&);

void merge_dict(const std::vector<Counter> & inputs, Counter & out);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Counter> freq_dict(argc - 1);
    std::vector<std::thread> threads(argc - 1);
    std::vector<int> codeResults(argc - 1);

    for (int i = 1; i < argc; ++i) {
        threads[i] = std::thread(run_count_words, argv[i], &freq_dict[i], &codeResults[i]);
    }
    
    for (auto& t : threads) {
        t.join();
    }

    for (const auto & codeResult : codeResults) {
        if (codeResult != 0) {
            return codeResult;
        }
    }

    Counter freq_dict_total;
    merge_dict( freq_dict, freq_dict_total);
    print_topk(std::cout, freq_dict_total, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void run_count_words(char * fname, Counter * result, int * codeResult) {
    std::ifstream input{ fname };
    if (!input.is_open()) {
        std::cerr << "Failed to open file " << fname << '\n';
        *codeResult = EXIT_FAILURE;
        return;
    }
    count_words(input, *result);
    *codeResult = 0;
    return;
}

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void merge_dict(const std::vector<Counter>& inputs, Counter& out) {
    for (const auto & input : inputs) {
        for (const auto & [word, count] : input) {
            out[word] += count;
        }
    }
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}