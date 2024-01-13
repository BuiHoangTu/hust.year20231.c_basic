cmake_minimum_required(VERSION 3.22)
project(InYear4_1 C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(minilib)
include_directories(minilib)

add_subdirectory(contest4)
add_subdirectory(contest6)
add_subdirectory(contest7)
add_subdirectory(contest8)
add_subdirectory(contest9)
add_subdirectory(contest10)
add_subdirectory(contest11)
add_subdirectory(contest12)


add_subdirectory(test2)
add_subdirectory(test3)


add_executable(prog main.c)
