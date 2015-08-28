project(digital_ant_farm)

cmake_minimum_required(VERSION 2.8.0)

include_directories("${CMAKE_SOURCE_DIR}/include")

#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB SRC src/*.cpp src/*.h)

#see http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake for proper ways to enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(ant_farm_lib ${SRC})
