project(digital_ant_farm)

#target_compile_options and add_compile_options only available since cmake 2.8.12
cmake_minimum_required(VERSION 2.8.12)

#set the default build type as "Release"
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build: Debug, Release, DebugWithWarnings, or DebugWithWarningsOptimized." FORCE)
endif()

#tell cmake where to find module scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/sdl2-cmake-scripts")

#need FLTK for GUI
set(FLTK_SKIP_FLUID 1)
find_package(FLTK REQUIRED)
include_directories(SYSTEM ${FLTK_INCLUDE_DIR}) #suppress warnings

#need SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(MAIN_TARGET "ant_farm_lib")
set(TEST_TARGET "tests")

#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB SRC src/*.cpp)

#see http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake for proper ways to enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add a property to both the main library and the test target
function(all_targets_compile_property)
    #see http://stackoverflow.com/questions/5096881/does-set-target-properties-in-cmake-override-cmake-cxx-flags 
    target_compile_options(${MAIN_TARGET} PRIVATE ${ARGN})
    target_compile_options(${TEST_TARGET} PRIVATE ${ARGN})
endfunction()

function(all_targets_compile_definitions def)
    target_compile_definitions(${MAIN_TARGET} PRIVATE ${def})
    target_compile_definitions(${TEST_TARGET} PRIVATE ${def})
endfunction()

#divide debug fields into common (i.e. non compiler-specific) debug flags, GCC-specific flags and clang-specific flags
########################################
#cmake list of flags
set(COMMON_DEBUG_FLAGS -g -Wall -Wextra -Wundef -Wcast-qual -Wconversion -Wformat=2 -Wshadow -ftrapv -Wuninitialized -Winit-self -Wcast-align -Wwrite-strings)

#Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn) doesn't support -faddress=sanitize
#NOTE THAT VALGRIND WILL NOT WORK WITH -fsanitize=address (the other flags do not seem to pose a problem)
set(CLANG_SANITIZE_ADDRESS_FLAG "-fsanitize=address")
set(GCC_OPTIMIZE_DEBUG "-Og")
########################################

function(EnableDebugWarnings)
    all_targets_compile_definitions("-DDEBUG") 

    all_targets_compile_property(${COMMON_DEBUG_FLAGS})

    #add clang-specific debugging flags
    #note: clang with apple modifications is named AppleClang (which will fail STREQUAL "Clang")
    #use MATCHES "Clang" to check for either kind of clang
    #see http://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
    if(("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang") AND NOT ${APPLE})
        message("Building with clang on a non-Apple machine.  Enabling -faddress=sanitize.")
        all_targets_compile_property("${CLANG_SANITIZE_ADDRESS_FLAG}")
    endif()
endfunction()

#-----------------------------------------------------------------------
#run ctags to generate tagfile
#see http://stackoverflow.com/questions/9827208/run-a-shell-command-ctags-in-cmake-and-make
#do NOT run on Windows or won't be able to find the ctags executable
if(NOT WIN32)
    set_source_files_properties( ctags.output PROPERTIES GENERATED true)
    #see http://stackoverflow.com/questions/1932396/c-source-tagging for explanation of ctags options
    add_custom_command ( OUTPUT ctags.output
        COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )

    add_library(${MAIN_TARGET} ${SRC} ctags.output)
else()
    add_library(${MAIN_TARGET} ${SRC})
endif()
#-----------------------------------------------------------------------

#link against FLTK and SDL2
target_link_libraries(${MAIN_TARGET} ${FLTK_LIBRARIES})
target_link_libraries(${MAIN_TARGET} ${SDL2_LIBRARY})

#build tests
#see https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt for example


#add google test
#gtest is directly checked into this repository to reduce build script complexity
#see http://stackoverflow.com/questions/9689183/cmake-googletest
#builds gtest in a subdirectory of the binary dir
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/gtest-1.7.0" ${CMAKE_BINARY_DIR}/gtest-bin)
set(ANTFLIB_GTEST_OPTIONS -Wp,-w -w)
target_compile_options(gtest PRIVATE ${ANTFLIB_GTEST_OPTIONS})
target_compile_options(gtest_main PRIVATE ${ANTFLIB_GTEST_OPTIONS})

include_directories(SYSTEM ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

#find test sources
#WARNING: CMAKE WON'T BE ABLE TO DETECT WHEN NEW SOURCE FILES ARE ADDED!
FILE(GLOB TESTS_SRC test/*.cpp )

add_executable(${TEST_TARGET} ${TESTS_SRC})

all_targets_compile_definitions("-DTESTING" )

if((${CMAKE_BUILD_TYPE} STREQUAL "DEBUG") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    message("Building in debug mode without warnings.")
    message("To enable warnings, pass -DCMAKE_BUILD_TYPE=DebugWithWarnings")
    #see http://stackoverflow.com/questions/5352074/how-to-create-a-c-define-for-a-certain-target-using-cmake
    all_targets_compile_definitions("-DDEBUG") 
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DebugWithWarnings")
    message("Building in debug mode with warnings.")
    message("To disable warnings, pass -DCMAKE_BUILD_TYPE=Debug")
    EnableDebugWarnings()
#GCC has an -Og option to enable optimizations that won't interfere with debugging
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DebugWithWarningsOptimized")
    EnableDebugWarnings()
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message("GNU compiler detected, building in optimized debug mode with warnings.")
        all_targets_compile_property("${GCC_OPTIMIZE_DEBUG}")
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
    all_targets_compile_definitions("-DNDEBUG")
endif()

#link libraries to test executable
target_link_libraries(${TEST_TARGET} gtest gtest_main)
target_link_libraries(${TEST_TARGET} ant_farm_lib)
target_link_libraries(${TEST_TARGET} ${FLTK_LIBRARIES})
target_link_libraries(${TEST_TARGET} ${SDL2_LIBRARY})


#copy the test resources directory into the bin directory so the tests executable can find it
file(COPY "res/test/" DESTINATION ${CMAKE_BINARY_DIR}/res/test)
