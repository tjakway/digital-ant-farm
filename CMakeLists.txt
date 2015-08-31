project(digital_ant_farm)

cmake_minimum_required(VERSION 2.8.0)

include_directories("${CMAKE_SOURCE_DIR}/include")

#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB SRC src/*.cpp src/*.h)

#see http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake for proper ways to enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if((${CMAKE_BUILD_TYPE} STREQUAL "DEBUG") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    message("Building in debug mode.")
    #see http://stackoverflow.com/questions/5352074/how-to-create-a-c-define-for-a-certain-target-using-cmake
    add_definitions( -DDEBUG )

    #add clang-specific debugging flags
    #see http://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        #NOTE THAT VALGRIND WILL NOT WORK WITH -fsanitize=address (the other flags do not seem to pose a problem)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wstrict-prototypes -Wundef -Wcast-qual -Wconversion -Wformat=2 -Wshadow -ftrapv -Wuninitialized -Winit-self -Wcast-align -Wwrite-strings")
    endif()

else((${CMAKE_BUILD_TYPE} STREQUAL "DEBUG") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    message("Not building in debug mode.")
    #disables assertions
    #see http://stackoverflow.com/questions/5354314/how-to-completely-disable-assertion
    #mandated by POSIX
    add_definitions( -DNDEBUG )
endif((${CMAKE_BUILD_TYPE} STREQUAL "DEBUG") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))

add_library(ant_farm_lib ${SRC})

#build tests
#see https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt for example

set(TESTS_EXE "tests")

#add google test
#gtest is directly checked into the repository to reduce build script complexity
#see http://stackoverflow.com/questions/9689183/cmake-googletest
#builds gtest in a subdirectory of the binary dir
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/gtest-1.7.0" ${CMAKE_BINARY_DIR}/gtest-bin)

#find test sources
#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB TESTS_SRC test/*.cpp test/*.h)

add_definitions( -DTESTING )

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${TESTS_EXE} ${TESTS_SRC})

target_link_libraries(${TESTS_EXE} gtest gtest_main)

target_link_libraries(${TESTS_EXE} ant_farm_lib)
