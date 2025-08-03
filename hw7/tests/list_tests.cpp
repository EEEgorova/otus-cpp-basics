#include <list>
#include <gtest/gtest.h>

TEST(List, Empty) {
    std::list container({ 12, 12, 5, 10});
    ASSERT_TRUE(!container.empty());

    container.clear();
    ASSERT_TRUE(container.empty());

}

TEST(List, Size) {
    std::list container({ 12, 12, 5, 10 });
    ASSERT_EQ( container.size(), 4);

    container.push_back(3);
    ASSERT_EQ(container.size(), 5);

    container.clear();
    ASSERT_EQ(container.size(), 0);

}

TEST(List, PushBack) {
    std::list container({ 12, 12, 5, 10 });
    std::list result({ 12, 12, 5, 10, 3 });

    container.push_back(3);
    ASSERT_EQ(container, result);
}

TEST(List, PushFront) {
    std::list container({ 12, 12, 5, 10 });
    std::list result({ 3, 12, 12, 5, 10 });

    container.push_front(3);
    ASSERT_EQ(container, result);
}

TEST(List, PopBack) {
    std::list container({ 12, 12, 5, 10 });
    std::list result({ 12, 12, 5 });
    
    container.pop_back();
    ASSERT_EQ(container, result);
}

TEST(List, PopFront) {
    std::list container({ 12, 12, 5, 10 });
    std::list result({ 12, 5, 10 });

    container.pop_front();
    ASSERT_EQ(container, result);
}

TEST(List, Insert) {
    {
        std::list container1({ 12, 12, 5, 10 });
        std::list result1({ 12, 12, 3, 5, 10 });

        size_t ind = container1.size() / 2 - 1;
        auto it = container1.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        int val = 3;
        container1.insert(it, val);
        ASSERT_EQ(container1, result1);
    }
    {
        std::list container2({ 12, 12, 5 });
        std::list result2({ 12, 3, 12, 5 });

        size_t ind = container2.size() / 2 - 1;
        auto it = container2.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        int val = 3;
        container2.insert(it, val);
        ASSERT_EQ(container2, result2);
    }
}

TEST(List, Erase) {
    {
        std::list container1({ 12, 3, 5, 10 });
        std::list result1({ 12, 3, 10 });

        size_t ind = container1.size() / 2 - 1;
        auto it = container1.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        container1.erase(it);
        ASSERT_EQ(container1, result1);
    }
    {
        std::list container2({ 12, 3, 5 });
        std::list result2({ 12, 5 });

        size_t ind = container2.size() / 2 - 1;
        auto it = container2.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        container2.erase(it);
        ASSERT_EQ(container2, result2);
    }
}

TEST(List, ElemAccess) {
    std::list container({ 12, 3, 5, 10 });
    
    size_t ind = container.size() / 2 - 1;
    auto it = container.begin();

    for (size_t i = 0; i <= ind; ++i) {
        ++it;
    }
    
    ASSERT_EQ(*it, 5);
}