cmake_minimum_required(VERSION 3.5)

project(uniq_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
add_executable(uniq_queue main.cpp)
target_link_libraries(uniq_queue Threads::Threads)
