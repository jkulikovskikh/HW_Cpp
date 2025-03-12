#include <gtest/gtest.h>
#include "containers.h"

struct ListFixture : public testing::Test {

    const size_t elementCount = 10;
    std::list<int> list; //the same list instance for all test cases

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
            list.push_back(i);
     }

    // You can define per-test tear-down logic as usual.
    void TearDown() override {
        std::cout << "TearDown" << std::endl;
        list.clear();
        // Nothing to do for now
    }
};

// Создание контейнера
TEST(List, CreateContainer) {
    std::list<int> list;

    EXPECT_EQ(list.size(), 0);
}

// Проверка выброса исключения при создании контейнера с невалидным размером
TEST(List, CreateContainerThrowExpection) {
    
    EXPECT_THROW(hw::MyList<int> list(0), std::invalid_argument);
}

// Проверка создания контейнера без выброса исключения
TEST(List, CreateContainerWithoutThrowExpection) {
    
    EXPECT_NO_THROW(hw::MyList<int> list(1));
    EXPECT_NO_THROW(hw::MyList<int> list);
}

// Проверка создания контейнера определенного размера
TEST(List, CreateContainerWithMaxSize) {

    size_t max_size = 3;
    hw::MyList<int> list(max_size);

    EXPECT_EQ(list.size(), max_size);
}

// Вставка нескольких элементов в пустой контейнер
TEST(List, InsertElements) {
    std::list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
}

// Удаление всех элементов из контейнера
TEST(List, EraseAllElements) {
    std::list<int> list;

    const size_t count = 10;
    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    for (size_t i = 0; i < count; ++i) {
        list.pop_back();
    }

    ASSERT_TRUE(list.empty());
}

// Вставка элемента в конец
TEST_F(ListFixture, InsertToEnd) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 5;
    list.push_back(value);

    EXPECT_EQ(list.size(), 11);
    EXPECT_EQ(list.back(), 5);

    size_t elements = -1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (iter != --list.end()) {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }     
    }
}

// Вставка элемента в начало
TEST_F(ListFixture, InsertToBegin) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 5;
    list.push_front(value);

    EXPECT_EQ(list.size(), 11);
    EXPECT_EQ(list.front(), 5);

    size_t elements = -1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (iter != list.begin()) {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }     
    }
}

// Вставка элемента в середину
TEST_F(ListFixture, InsertToMiddle) {
    std::cout << "Test body" << std::endl;
   
    size_t value = 10;
    auto iter_middle = 5;

    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (*iter == iter_middle) {
            list.insert(++iter, value);
            break;
        }
    }

    EXPECT_EQ(list.size(), 11);

    size_t elements = -1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) { 
        if (*iter == iter_middle) {
            EXPECT_TRUE(*(++iter) == value);
            elements++;
        }
        else {
            elements ++;
            EXPECT_EQ(*iter , elements);
        }
    }
}

// Удаление элементов из конца
TEST_F(ListFixture, EraseFromEnd) {
    std::cout << "Test body" << std::endl;
   
    list.pop_back();

    EXPECT_EQ(list.size(), 9);
    EXPECT_EQ(list.back(), 8);
}

// Удаление элементов из начала
TEST_F(ListFixture, EraseFromBegin) {
    std::cout << "Test body" << std::endl;
   
    list.pop_front();

    EXPECT_EQ(list.size(), 9);
    EXPECT_EQ(list.front(), 1);

    size_t elements = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
            elements ++;
            EXPECT_EQ(*iter , elements);  
    }
}

// Удаление элементов из середины
TEST_F(ListFixture, EraseFromMiddle) {
    std::cout << "Test body" << std::endl;
   
    auto iter_middle = 5;

    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (*iter == iter_middle) {
            list.erase(iter);
            break;
        } 
    }
   
    EXPECT_EQ(list.size(), 9);

    size_t elements = -1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (*iter == 4) {
            EXPECT_TRUE(*(++iter) != iter_middle);
            elements += 2;
        }
        elements ++;
        EXPECT_EQ(*iter , elements);
    }
}


// Получение элементов из контейнера
TEST_F(ListFixture, GetElements) {
    std::cout << "Test body" << std::endl;
   
    size_t size_container = 0;
    size_t value = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        EXPECT_EQ(*iter , value);
        value++;
        size_container++;
    }
 
    EXPECT_EQ(size_container, elementCount);
}

// Получение размера контейнера (фактическое количество элементов)
TEST_F(ListFixture, GetSize) {
    std::cout << "Test body" << std::endl;

    EXPECT_EQ(list.size(), elementCount);
}

