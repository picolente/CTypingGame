cmake_minimum_required(VERSION 3.30)
project(TypingGame C)

set(CMAKE_C_STANDARD 11)

add_executable(TypingGame main.c
        libs/wordbuffer.c
        libs/wordbuffer.h)
