cmake_minimum_required(VERSION 3.7)
project(cacheEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp cacheStore.h lib.h)
add_executable(cacheEngine ${SOURCE_FILES})