cmake_minimum_required(VERSION 3.28.3)
project(JohnKopernicus C)

set(CMAKE_C_STANDARD 11)

add_executable(JohnKopernicus JohnKopernicus.c
        DeltaV.c
        DeltaV.h)

target_link_libraries(JohnKopernicus m)
