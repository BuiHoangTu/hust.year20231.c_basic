cmake_minimum_required(VERSION 3.22)
project(Contest12 C)


add_executable(binary_sequence_no_subseq binary_sequence_no_subseq.c)


add_executable(family_tree family_tree.c)
target_link_libraries(family_tree minilib)
configure_file(family_tree.txt family_tree.txt COPYONLY)
