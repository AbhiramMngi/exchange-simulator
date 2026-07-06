cmake_minimum_required(VERSION 3.20)

project(exchange_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_library(exchange 
    src/orderbook/Orderbook.cpp
    src/orders/Order.cpp
)

add_executable(run_exchange
    src/main.cpp
)

target_include_directories(exchange
    PUBLIC
        include
)

target_link_libraries(run_exchange PRIVATE exchange)



FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)