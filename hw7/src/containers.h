#pragma once

#include <list>
#include <vector>

#include <stdexcept>

namespace hw {
    template <typename T>
    class MyVector {
        public:
        MyVector() {}

        ~MyVector() {}

        MyVector (size_t max_size) {
            if (max_size == 0) {
                throw std::invalid_argument("Maxsimum container size must be greater than 0");
            }
            else {
                for (int i = 0; i < max_size; ++i) {
                    v.push_back(0);
                }
            }
        }

        std::size_t size() const {
            return v.size();
        }
        
        private: 
            std::vector<T> v;
    };

    template <typename T>
    class MyList {
        public:
        MyList() {}

        ~MyList() {}

        MyList (size_t max_size) {
            if (max_size == 0) {
                throw std::invalid_argument("Maxsimum container size must be greater than 0");
            }
            else {
                for (int i = 0; i < max_size; ++i) {
                    l.push_back(0);
                }
            }
        }

        std::size_t size() const {
            return l.size();
        }

        private: 
            std::list<T> l;
    };
}

