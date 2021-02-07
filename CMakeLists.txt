cmake_minimum_required(VERSION 3.5)

project(join_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (headers "." "data/")

include_directories(headers)

add_executable(join_server main.cpp data/tables.cpp)
