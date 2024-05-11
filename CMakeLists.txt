cmake_minimum_required(VERSION 3.28)
project(Cdataframe C)

set(CMAKE_C_STANDARD 11)

add_library(Cdataframe STATIC cdataframe.c
        column.c
        column.h
        main.c)
