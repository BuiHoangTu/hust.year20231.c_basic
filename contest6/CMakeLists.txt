cmake_minimum_required(VERSION 3.26)
project(Contest6 C)


add_executable(select_sort_interger select_sort_interger.c)
target_link_libraries(select_sort_interger minilib)

add_executable(sap_xep_danh_sach sap_xep_danh_sach.c)
target_link_libraries(sap_xep_danh_sach minilib)