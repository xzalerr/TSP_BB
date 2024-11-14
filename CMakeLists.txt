cmake_minimum_required(VERSION 3.27)
project(TSP_BB)

set(CMAKE_CXX_STANDARD 20)

add_executable(TSP_BB main.cpp
        DataGenerator.h
        DataGenerator.cpp
        ProblemSolver.cpp
        ProblemSolver.h
)
