cmake_minimum_required(VERSION 4.1)
project(pcmio)

set(CMAKE_CXX_STANDARD 20)

add_executable(pcmio_tests tests.c
        pcmio.h)

