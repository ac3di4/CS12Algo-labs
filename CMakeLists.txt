cmake_minimum_required(VERSION 3.2)

project(lab)

add_library(libstr src/lstr.c)

add_executable(main src/main.c)
target_link_libraries(main libstr)