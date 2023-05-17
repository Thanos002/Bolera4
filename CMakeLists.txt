cmake_minimum_required(VERSION 3.21)
project(Bolera4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bolera4
        Bolera.c
        Bolera.h
        IncFile1.h
        Lanzador.c
        Lanzador.h
        LED_Display.asm
        main.c)
