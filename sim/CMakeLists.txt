cmake_minimum_required(VERSION 3.10)
project(sim C)

set(CMAKE_C_STANDARD 99)

add_executable(sim simulator.c bstr.c bstr.h comp.c comp.h)