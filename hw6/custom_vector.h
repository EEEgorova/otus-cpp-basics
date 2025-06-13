#pragma once
#include "array_ptr.h"
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>


template <typename Type>
class CustomVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;
    
    CustomVector() noexcept = default;
    
    // Создаёт вектор из std::initializer_list
    CustomVector(std::initializer_list<Type> init)
        : store_(init.size()),
        size_(init.size()),
        capacity_(init.size())
    {
        std::copy(init.begin(), init.end(), store_.Get());
    }

    // Возвращает количество элементов в массиве
    size_t GetSize() const noexcept {
        return size_;
    }
    
    // Возвращает ссылку на элемент с индексом index
    Type& operator[](size_t index) noexcept {
        return store_[index];
    }
    
    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    Type& At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index > size");
        }

        return store_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    const Type& At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index > size");
        }

        return store_[index];
    }

    // Обнуляет размер массива, не изменяя его вместимость
    void Clear() noexcept {
        size_ = 0;
    }

    // Изменяет размер массива.
    // При увеличении размера новые элементы получают значение по умолчанию для типа Type
    void Resize(size_t new_size) {
        if (new_size <= size_) {
            size_ = new_size;
            return;
        }

        if (new_size > capacity_) {
            auto capacity_new = std::max(new_size, capacity_ * 2);
            Reserve(capacity_new);

        }

        DefaultFill(store_.Get() + size_, store_.Get() + new_size);
        size_ = new_size;
        return;

    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        ArrayPtr<Type> store_new(new_capacity);
        std::move(store_.Get(), store_.Get() + size_, store_new.Get());
        store_.swap(store_new);
        capacity_ = new_capacity;
        return;
    }

    void DefaultFill(Iterator start, Iterator finish) {
        std::generate(start, finish, []() {return Type{}; });
    }

    // Возвращает итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator begin() noexcept {
        return store_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator end() noexcept {
        return store_.Get() + size_;
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator begin() const noexcept {
        return store_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator end() const noexcept {
        return store_.Get() + size_;
    }
    
    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cbegin() const noexcept {
        return store_.Get();
    }
    
    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cend() const noexcept {
        return store_.Get() + size_;
    }

    // Добавляет элемент в конец вектора
    // При нехватке места увеличивает вдвое вместимость вектора
    void PushBack(const Type& item) {
        if (size_ == capacity_) {
            Resize(size_ + 1);
            store_[size_ - 1] = item;
        }
        else {
            store_[size_] = item;
            ++size_;
        }
    }
   
    // Вставляет значение value в позицию pos.
    // Возвращает итератор на вставленное значение
    // Если перед вставкой значения вектор был заполнен полностью,
    // вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
    Iterator Insert(int i, const Type& value) {
        ConstIterator pos = cbegin() + i;
        Iterator it = CommonInsert(pos);
        *(it) = value;
        return it;
    }
    
    // Удаляет элемент вектора в указанной позиции
    Iterator Erase(int i) {
        ConstIterator pos = cbegin() + i;
        if (!(pos >= cbegin() && pos <= cend())) {
            throw std::invalid_argument("Iterator is out of range");
        }

        auto offset = pos - cbegin();
        Iterator it = begin() + offset;
        std::move(it + 1, end(), it);
        --size_;

        return it;
    }
    

private:
    ArrayPtr<Type> store_;
    size_t size_ = 0;
    size_t capacity_ = 0;

    Iterator CommonInsert(ConstIterator pos) {
        auto offset = pos - cbegin();
        Reserve(size_ + 1);
        ++size_;
        std::move_backward(begin() + offset, end() - 1, end());
        Iterator it = begin() + offset;

        return it;
    }
};

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const CustomVector<Type>& container ) {
    for (int a : container) {
        std::cout << a << " ";

    }
    std::cout << std::endl;
    return os;
}

