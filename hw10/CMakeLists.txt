cmake_minimum_required(VERSION 3.15)

project(chat)

include(FetchContent)

FetchContent_Declare(asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-29-0)
FetchContent_MakeAvailable(asio)

add_executable(chat 
        Server.h 
        Server.cpp 
        Client.h 
        Client.cpp 
        Functions.h 
        Functions.cpp
        main.cpp)

target_include_directories(chat PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_compile_definitions(chat PRIVATE ASIO_STANDALONE)

set_target_properties(chat PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(chat PRIVATE /utf-8)
else()
    target_compile_options(chat PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()