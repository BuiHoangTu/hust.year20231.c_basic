cmake_minimum_required(VERSION 3.22)
project(Contest8 C)


add_executable(heap_sort_int_arr heap_sort_int_arr.c)
target_link_libraries(heap_sort_int_arr minilib)

add_executable(heap_sort_danh_sach heap_sort_danh_sach.c)
target_link_libraries(heap_sort_danh_sach minilib)
