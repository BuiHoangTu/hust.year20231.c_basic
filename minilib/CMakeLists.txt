cmake_minimum_required(VERSION 3.22)
project(mini_library VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

# ON by default, use -DNOWARN=ON/OFF in Cmake command to turn ON/OFF
option(BENCH_OP "Optimization (O1, O2, O3) benchmark" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -w")
endif()


### library ###
add_library(minilib
        array/array_list.c
        array/array_list.h
        core/heap.c
        core/heap.h
        core/type.c
        core/type.h
        list/double_linked_list.c
        list/double_linked_list.h
        list/queue.c
        list/queue.h
        list/single_linked_list.c
        list/single_linked_list.h
        list/stack.c
        list/stack.h
        tree/binary_tree.c
        tree/binary_tree.h
        tree/tree.c
        tree/tree.h
        sort/selection_sort.c
        sort/selection_sort.h
        sort/merge_sort.c
        sort/merge_sort.h
        sort/heap_sort.c
        sort/heap_sort.h
        search/binary_search.c
        search/binary_search.h
        map/hash_map.c
        map/hash_map.h
        core/hash.h
        core/hash.c
)

### test ###
add_subdirectory(tests)


### install ###
if (${CMAKE_BUILD_TYPE} STREQUAL Release AND
        ${CMAKE_PROJECT_NAME} STREQUAL mini)
    set(mini_include_dest "include")
    set(mini_lib_dest "lib")
    set(MERGE_CMD ${CMAKE_CURRENT_BINARY_DIR}/mega-unit/merge)
    MESSAGE(STATUS "MERGE CMD: " ${MERGE_CMD})
    execute_process(COMMAND ${MERGE_CMD}
            ${CMAKE_CURRENT_SOURCE_DIR} mini.h minilib.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    execute_process(COMMAND ${MERGE_CMD}
            ${CMAKE_CURRENT_SOURCE_DIR} mini.c minilib.c
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/minilib.h DESTINATION "${mini_include_dest}")
    install(TARGETS minilib DESTINATION "${mini_lib_dest}")

    set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Bùi Hoàng Tú")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION
            "Thư viện cấu trúc dữ liệu mini.")
    set(CMAKE_PROJECT_HOMEPAGE_URL "")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "standard")
    set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

    file (READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION MINI_VERSION)

    # Set a Package Version
    set(CPACK_PACKAGE_VERSION "${MINI_VERSION}")
    include(CPack)
endif()