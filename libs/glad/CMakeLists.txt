cmake_minimum_required(VERSION 3.16.3)

add_library(glad src/glad.c include/glad/glad.h)

target_include_directories(glad PUBLIC include/)
