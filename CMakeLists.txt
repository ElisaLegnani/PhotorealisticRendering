cmake_minimum_required(VERSION 3.12)

project(raytracer
    VERSION 1.0
    DESCRIPTION "Hello world in C++"
    LANGUAGES CXX
    )
    
enable_testing()

add_library(trace
    src/raytracer.cpp
    )

target_include_directories(trace PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

add_executable(raytracer
    src/raytracer.cpp
    )

target_link_libraries(raytracer PUBLIC trace)

add_executable(colortest
    test/colors.cpp
    )

target_link_libraries(colortest PUBLIC trace)

add_test(NAME colortest
    COMMAND colortest 
    )

add_executable(hdrimagetest
    test/hdrimage.cpp
    )

target_link_libraries(hdrimagetest PUBLIC trace)

add_test(NAME hdrimagetest
    COMMAND hdrimagetest
    )
    
target_compile_features(raytracer PUBLIC cxx_std_17)
