cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(raytracer
    VERSION 1.0
    DESCRIPTION "Photorealistic Rendering in C++"
    LANGUAGES CXX
    )
    
enable_testing()

# MY LIBRARIES DECLARATIONS:
add_library(trace
    src/hdrimage.cpp
    src/transformation.cpp
    )


# PATH TO MY LIBRARIES:
target_include_directories(trace PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

# OTHER LIBRARIES:
include(FindPkgConfig)
pkg_check_modules(GDLIB REQUIRED gdlib)

#include_directories(${GDLIB_INCLUDE_DIRS})
#link_directories(${GDLIB_LIBRARY_DIRS})
#link_libraries(${GDLIB_LIBRARIES})

# EXECUTABLE:
add_executable(raytracer
    src/raytracer.cpp
    )

target_include_directories(trace PUBLIC ${GDLIB_INCLUDE_DIRS})
target_link_directories(trace PUBLIC ${GDLIB_LIBRARY_DIRS})
target_compile_options(trace PUBLIC ${GDLIB_CFLAGS})
target_link_libraries(trace PUBLIC ${GDLIB_LIBRARIES})

#target_include_directories(raytracer PUBLIC ${GDLIB_INCLUDE_DIRS})
#target_link_directories(raytracer PUBLIC ${GDLIB_LIBRARY_DIRS})
#target_compile_options(raytracer PUBLIC ${GDLIB_CFLAGS})
#target_link_libraries(raytracer PUBLIC ${GDLIB_LIBRARIES} trace)
target_link_libraries(raytracer PUBLIC trace)


# TESTS:
#  colortest
add_executable(colortest
    test/colors.cpp
    )

target_link_libraries(colortest PUBLIC trace)

add_test(NAME colortest
    COMMAND colortest 
    )

#  hdrimagetest
add_executable(hdrimagetest
    test/hdrimage.cpp
    )
target_link_libraries(hdrimagetest PUBLIC trace)

add_test(NAME hdrimagetest
    COMMAND hdrimagetest
    )

# geometrytest
add_executable(geometrytest
    test/geometry.cpp
    )

target_link_libraries(geometrytest PUBLIC trace)

add_test(NAME geometrytest
    COMMAND geometrytest
    )

# transformationtest
add_executable(transformationtest
    test/transformation.cpp
    )

target_link_libraries(transformationtest PUBLIC trace)

add_test(NAME transformationtest
    COMMAND transformationtest
    )

# raytest
add_executable(raytest
    test/ray.cpp
    )

target_link_libraries(raytest PUBLIC trace)

add_test(NAME raytest
    COMMAND raytest
    )

# camera
add_executable(cameratest
    test/camera.cpp
    )

target_link_libraries(cameratest PUBLIC trace)

add_test(NAME cameratest
    COMMAND cameratest
    )

# imagetracer
add_executable(imagetracertest
    test/imagetracer.cpp
    )

target_link_libraries(imagetracertest PUBLIC trace)

add_test(NAME imagetracertest
    COMMAND imagetracertest
    )
    
# COMPILER FEAUTURES:
target_compile_features(raytracer PUBLIC cxx_std_17)
