cmake_minimum_required(VERSION 3.12)

project(hw9)

add_executable(topk_words 
topk_words.cpp
)

add_executable(topk_words_threads 
topk_words_threads.cpp
)

add_executable(topk_words_mutex 
topk_words_mutex.cpp
)

set_target_properties(topk_words PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(topk_words_threads PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(topk_words_mutex PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)