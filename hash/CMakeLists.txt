cmake_minimum_required(VERSION 3.17)
project(hash C)

set(CMAKE_C_STANDARD 11)

add_executable(hash main.c hash_tbl.c hash_tbl.h comm.c comm.h)