cmake_minimum_required(VERSION 3.10)
project(LimitOrderBookSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(simulator
    src/main.cpp
    src/MatchingEngine.cpp
    )
