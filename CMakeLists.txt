project(digital_ant_farm)

cmake_minimum_required(VERSION 2.8.0)

include_directories("${CMAKE_SOURCE_DIR}/include")

#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB SRC src/*.cpp src/*.h)

#see http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake for proper ways to enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#divide debug fields into common (i.e. non compiler-specific) debug flags, GCC-specific flags and clang-specific flags
########################################
set(COMMON_DEBUG_FLAGS "-g -Wall -Wextra -Wstrict-prototypes -Wundef -Wcast-qual -Wconversion -Wformat=2 -Wshadow -ftrapv -Wuninitialized -Winit-self -Wcast-align -Wwrite-strings")

#Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn) doesn't support -faddress=sanitize
#NOTE THAT VALGRIND WILL NOT WORK WITH -fsanitize=address (the other flags do not seem to pose a problem)
set(CLANG_SANITIZE_ADDRESS_FLAG "-fsanitize=address")
set(GCC_OPTIMIZE_DEBUG "-Og")
########################################

function(EnableDebugWarnings)
    add_definitions( -DDEBUG ) 
    #enable non-compiler specific flags
    #by default variables set in a function are in local scope!  need PARENT_SCOPE to modify global variables
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_DEBUG_FLAGS}" PARENT_SCOPE)

    #add clang-specific debugging flags
    #note: clang with apple modifications is named AppleClang (which will fail STREQUAL "Clang")
    #use MATCHES "Clang" to check for either kind of clang
    #see http://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
    if(("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang") AND NOT ${APPLE})
        message("Building with clang on a non-Apple machine.  Enabling -faddress=sanitize.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_SANITIZE_ADDRESS_FLAG}" PARENT_SCOPE)
    endif()
endfunction()

if((${CMAKE_BUILD_TYPE} STREQUAL "DEBUG") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    message("Building in debug mode without warnings.")
    message("To enable warnings, pass -DCMAKE_BUILD_TYPE=DebugWithWarnings")
    #see http://stackoverflow.com/questions/5352074/how-to-create-a-c-define-for-a-certain-target-using-cmake
    add_definitions( -DDEBUG )
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DebugWithWarnings")
    message("Building in debug mode with warnings.")
    message("To disable warnings, pass -DCMAKE_BUILD_TYPE=Debug")
    EnableDebugWarnings()
#GCC has an -Og option to enable optimizations that won't interfere with debugging
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DebugWithWarningsOptimize")
    EnableDebugWarnings()
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message("GNU compiler detected, building in optimized debug mode with warnings.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_OPTIMIZE_DEBUG}")
    else()
        message("WARNING: COMPILER IS NOT GNU" WARNING)
        message("CANNOT BUILD IN OPTIMIZED DEBUG MODE!" WARNING)
        message("BUILDING IN DebugWithWarnings MODE!" WARNING)
    endif()
else()
    message("Not building in debug mode.")
    #disables assertions
    #see http://stackoverflow.com/questions/5354314/how-to-completely-disable-assertion
    #mandated by POSIX
    add_definitions( -DNDEBUG )
endif()

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
