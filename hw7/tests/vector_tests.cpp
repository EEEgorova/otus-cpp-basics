#include <vector>
#include <gtest/gtest.h>

TEST(Vector, Empty) {
    std::vector container({ 12, 12, 5, 10 });
    ASSERT_TRUE(!container.empty());

    container.clear();
    ASSERT_TRUE(container.empty());

}

TEST(Vector, Size) {
    std::vector container({ 12, 12, 5, 10 });
    ASSERT_EQ(container.size(), 4);

    container.push_back(3);
    ASSERT_EQ(container.size(), 5);

    container.clear();
    ASSERT_EQ(container.size(), 0);

}

TEST(Vector, PushBack) {
    std::vector container({ 12, 12, 5, 10 });
    std::vector result({ 12, 12, 5, 10, 3 });

    container.push_back(3);
    ASSERT_EQ(container, result);
}

TEST(Vector, InsertFront) {
    std::vector container({ 12, 12, 5, 10 });
    std::vector result({ 3, 12, 12, 5, 10 });

    container.insert(container.begin(), 3);
    ASSERT_EQ(container, result);
}

TEST(Vector, PopBack) {
    std::vector container({ 12, 12, 5, 10 });
    std::vector result({ 12, 12, 5 });

    container.pop_back();
    ASSERT_EQ(container, result);
}

TEST(Vector, EraseFront) {
    std::vector container({ 12, 12, 5, 10 });
    std::vector result({ 12, 5, 10 });

    container.erase(container.begin());
    ASSERT_EQ(container, result);
}

TEST(Vector, Insert) {
    {
        std::vector container1({ 12, 12, 5, 10 });
        std::vector result1({ 12, 12, 3, 5, 10 });

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
        std::vector container2({ 12, 12, 5 });
        std::vector result2({ 12, 3, 12, 5 });

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

TEST(Vector, Erase) {
    {
        std::vector container1({ 12, 3, 5, 10 });
        std::vector result1({ 12, 3, 10 });

        size_t ind = container1.size() / 2 - 1;
        auto it = container1.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        container1.erase(it);
        ASSERT_EQ(container1, result1);
    }
    {
        std::vector container2({ 12, 3, 5 });
        std::vector result2({ 12, 5 });

        size_t ind = container2.size() / 2 - 1;
        auto it = container2.begin();

        for (size_t i = 0; i <= ind; ++i) {
            ++it;
        }
        container2.erase(it);
        ASSERT_EQ(container2, result2);
    }
}

TEST(Vector, ElemAccess) {
    std::vector container({ 12, 3, 5, 10 });

    size_t ind = container.size() / 2 - 1;
    ASSERT_EQ(container[ind], 3);
    ASSERT_EQ(container.at(ind), 3);
}


