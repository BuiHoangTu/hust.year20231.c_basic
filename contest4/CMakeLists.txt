cmake_minimum_required(VERSION 3)
project(Contest4 C)


add_executable(tree_manipulation tree_manipulation.c)
target_link_libraries(tree_manipulation minilib)

## check system binary type
#if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(i386)|(I386)")
#    set(TARGET_ARCH "elf32-i386")
#    message(STATUS "sys architecture is elf32-i386")
#elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(X86_64)|(AMD64)|(amd64)")
#    set(TARGET_ARCH "elf64-x86-64")
#    message(STATUS "sys architecture is elf64-x86-64")
#else()
#    message(FATAL_ERROR "Unsupported architecture")
#endif()
#
#
#add_custom_command(TARGET tree_manipulation
#        POST_BUILD COMMAND objcopy
#        --input binary
#        --output ${TARGET_ARCH}
#        --binary-architecture i386
#        tree_manipulation.exe tree_manipulation_compiled.c)
