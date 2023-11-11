cmake_minimum_required(VERSION 3.26)
project(pid_simplex)

set(CMAKE_CXX_STANDARD 11)

add_executable(simplex simplex.cpp
        DifferentialEvolution.h
        TestFunctions.h
        DifferentialEvolution.h)
