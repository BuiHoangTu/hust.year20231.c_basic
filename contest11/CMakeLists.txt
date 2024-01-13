cmake_minimum_required(VERSION 3.22)
project(Contest11 C)


add_executable(bank_transaction bank_transaction.c)
target_link_libraries(bank_transaction minilib)
configure_file(bank_transaction.txt bank_transaction.txt COPYONLY)
