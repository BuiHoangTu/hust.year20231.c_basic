cmake_minimum_required(VERSION 3.22)
project(Contest9 C)


add_executable(pair_sum pair_sum.c)
target_link_libraries(pair_sum minilib)

add_executable(quan_ly_ho_so quan_ly_ho_so.c)
target_link_libraries(quan_ly_ho_so minilib)