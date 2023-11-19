cmake_minimum_required(VERSION 3.26)
project(mini_library C)

set(CMAKE_C_STANDARD 11)

add_library(minilib
        array/array_list.c
        array/array_list.h)
