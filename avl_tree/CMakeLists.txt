cmake_minimum_required(VERSION 3.17)
project(avl_tree C)

set(CMAKE_C_STANDARD 11)

add_executable(avl_tree main.c avl_tree.c avl_tree.h comm.c comm.h)