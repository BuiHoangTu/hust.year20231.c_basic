cmake_minimum_required(VERSION 3.22)
project(Contest10 C)


add_executable(word_frequency word_frequency.c)
target_link_libraries(word_frequency minilib)
configure_file(test_source.txt test_source.txt COPYONLY)

#
#add_executable(quan_ly_ho_so quan_ly_ho_so.c)
#target_link_libraries(quan_ly_ho_so minilib)