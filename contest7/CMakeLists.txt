cmake_minimum_required(VERSION 3.22)
project(Contest7 C)


add_executable(qsort_int_arr qsort_int_arr.c)
target_link_libraries(qsort_int_arr minilib)

add_executable(qsort_danh_sach qsort_danh_sach.c)
