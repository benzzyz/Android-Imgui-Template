cmake_minimum_required(VERSION 3.10)
project(mod)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow Android toolchain to be provided via -DCMAKE_TOOLCHAIN_FILE
if(NOT ANDROID)
  message(STATUS "Building for host? Ensure ANDROID toolchain is set when cross-compiling.")
endif()

add_library(mod SHARED
    src/android_mod.cpp
    src/pattern_scan.cpp
)

find_library(log-lib log)

target_include_directories(mod PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(mod ${log-lib})
