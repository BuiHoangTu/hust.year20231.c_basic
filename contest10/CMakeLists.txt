cmake_minimum_required(VERSION 3.22)
project(Contest10 C)


add_executable(word_frequency word_frequency.c)
target_link_libraries(word_frequency minilib)
configure_file(test_source.txt test_source.txt COPYONLY)

add_executable(hash_string hash_string.c)

add_executable(search_string search_string.c)
target_link_libraries(search_string minilib)

