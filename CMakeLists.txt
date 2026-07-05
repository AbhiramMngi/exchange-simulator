cmake_minimum_required(VERSION 3.20)

project(exchange LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_executable(run_exchange
    src/main.cpp
)