cmake_minimum_required(VERSION 3.28.3)
project(KSP C)

set(CMAKE_C_STANDARD 11)

add_executable(KSP JohnKopernicus.c
        DeltaV.c
        DeltaV.h)
