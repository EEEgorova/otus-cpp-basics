#include <cassert>
#include <iostream>
#include "custom_vector.h"
#include "custom_list.h"

// Эта функция проверяет работу контейнера на базовые операции
template <typename Custom>
void Test( Custom & container) {
    
    std::cout << container << std::endl;
    std::cout << container.GetSize() << std::endl;

    for (int i = 2; i < 5; ++i) {
        container.Erase(i);
    }
    std::cout << container << std::endl;

    container.Insert(0, 10);

    std::cout << container << std::endl;

    container.Insert(container.GetSize() / 2, 20);

    std::cout << container << std::endl;

    container.PushBack(30);

    std::cout << container << std::endl;
}


int main() {
    CustomVector test_vec({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Test(test_vec);

    CustomVector test_list({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Test(test_list);
}
