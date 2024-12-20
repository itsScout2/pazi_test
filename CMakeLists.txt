cmake_minimum_required(VERSION 3.30)
project(untitled C)

set(CMAKE_C_STANDARD 23)

set(SOURCES
        main.c
        binomial.c
        binomial.h
        binomial_table.c
        binomial_table.h
        frequency.c
        frequency.h
        runs.c
        runs.h
        lengths.c
        lengths.h
)

add_executable(untitled ${SOURCES})
