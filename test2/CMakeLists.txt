cmake_minimum_required(VERSION 3.22)
project(Test2 C)


add_executable(count_binary_nodes_with_2_children count_binary_nodes_with_2_children.c)
target_link_libraries(count_binary_nodes_with_2_children minilib)
#
#add_executable(quan_ly_ho_so quan_ly_ho_so.c)
#target_link_libraries(quan_ly_ho_so minilib)