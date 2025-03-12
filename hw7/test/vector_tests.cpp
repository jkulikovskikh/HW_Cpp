#include <gtest/gtest.h>
#include "containers.h"

struct VectorFixture : public testing::Test {

    const size_t elementCount = 10;
    std::vector<int> vector; //the same list instance for all test cases

    // Per-test-suite set-up.
    static void SetUpTestSuite() {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    // Per-test-suite tear-down.
    static void TearDownTestSuite() {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    // Per-test set-up
    void SetUp() override { 
        std::cout << "SetUp" << std::endl;

        // Create list with elementCount elements
        for (size_t i = 0; i < elementCount; ++i) 
            vector.push_back(i);
     }

    // You can define per-test tear-down logic as usual.
    void TearDown() override {
        std::cout << "TearDown" << std::endl;
        vector.clear();
        // Nothing to do for now
    }
};

// Создание контейнера
TEST(Vector, CreateContainer) {
    std::vector<int> vector;

    const size_t expectedZeroSize = 0;

    const auto curSize = vector.size();

    EXPECT_EQ(curSize, expectedZeroSize);
}

// Проверка выброса исключения при создании контейнера с невалидным размером
TEST(Vector, CreateContainerThrowExpection) {
    
    EXPECT_THROW(hw::MyVector<int> vector(0), std::invalid_argument);
}

// Проверка создания контейнера без выброса исключения
TEST(Vector, CreateContainerWithoutThrowExpection) {

    EXPECT_NO_THROW(hw::MyVector<int> vector);
    EXPECT_NO_THROW(hw::MyVector<int> vector(1));
}

// Проверка создания контейнера определенного размера
TEST(Vector, CreateContainerWithMaxSize) {

    size_t max_size = 3;
    hw::MyVector<int> vector(max_size);

    EXPECT_EQ(vector.size(), max_size);
}

// Вставка нескольких элементов в пустой контейнер
TEST(Vector, InsertElements) {
    std::vector<int> vector;

    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    EXPECT_EQ(vector.size(), 3);
}

// Удаление всех элементов из контейнера
TEST(Vector, EraseAllElements) {
    std::vector<int> vector;

    const size_t count = 10;
    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    for (size_t i = 0; i < count; ++i) {
        vector.pop_back();
    }

    ASSERT_TRUE(vector.empty());
}

// Вставка элемента в конец
TEST_F(VectorFixture, InsertToEnd) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 5;
    vector.push_back(value);

    EXPECT_EQ(vector.size(), 11);
    EXPECT_EQ(vector.back(), 5);

    size_t elements = -1;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        if (iter != --vector.end()) {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }     
    }
}

// Вставка элемента в начало
TEST_F(VectorFixture, InsertToBegin) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 5;
    auto iter_begin = vector.begin();
    vector.insert(iter_begin, value);

    EXPECT_EQ(vector.size(), 11);
    EXPECT_EQ(vector.front(), 5);

    size_t elements = -1;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        if (iter != vector.begin()) {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }     
    }
}

// Вставка элемента в середину
TEST_F(VectorFixture, InsertToMiddle) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 10;
    auto iter_middle = 5;

    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        if (*iter == iter_middle) {
            vector.insert(++iter, value);
            break;
        }
    }

    EXPECT_EQ(vector.size(), 11);

    size_t elements = -1;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) { 
        if (*iter == iter_middle) {
            EXPECT_TRUE(*(++iter) == value);
            elements ++;
        }
        else {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }
    }
}


// Удаление элементов из конца
TEST_F(VectorFixture, EraseFromEnd) {
    std::cout << "Test body" << std::endl;
   
    vector.pop_back();

    EXPECT_EQ(vector.size(), 9);
    EXPECT_EQ(vector.back(), 8);
}

// Удаление элементов из начала
TEST_F(VectorFixture, EraseFromBegin) {
    std::cout << "Test body" << std::endl;
   
    auto iter_begin = vector.begin();
    vector.erase(iter_begin);

    EXPECT_EQ(vector.size(), 9);
    EXPECT_EQ(vector.front(), 1);

    size_t elements = 0;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
            elements ++;
            EXPECT_EQ(*iter , elements);  
    }
}

// Удаление элементов из середины
TEST_F(VectorFixture, EraseFromMiddle) {
    std::cout << "Test body" << std::endl;
   
    auto iter_middle = 5;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        if (*iter == iter_middle) {
            vector.erase(iter);
            break;
        } 
    }
   
    EXPECT_EQ(vector.size(), 9);

    size_t elements = -1;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        if (*iter == 4) {
            EXPECT_TRUE(*(++iter) != iter_middle);
            elements += 2;
        }
        elements ++;
        EXPECT_EQ(*iter , elements);
    }
}

// Получение элементов из контейнера
TEST_F(VectorFixture, GetElements) {
    std::cout << "Test body" << std::endl;
   
    size_t size_container = 0;
    size_t value = 0;
    for (auto iter = vector.begin(); iter != vector.end(); ++iter) {
        EXPECT_EQ(*iter , value);
        value++;
        size_container++;
    }
 
    EXPECT_EQ(size_container, elementCount);

    value = 0;
    for (int i = 0; i < elementCount; ++i) {
        EXPECT_EQ(vector[i] , value);
        value++;
    }
}

// Получение размера контейнера (фактическое количество элементов)
TEST_F(VectorFixture, GetSize) {
    std::cout << "Test body" << std::endl;

    EXPECT_EQ(vector.size(), elementCount);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}