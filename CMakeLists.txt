target_include_directories(trace PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE.include>
    )

add_executable(raytracer
    src/raytracer.cpp
    )

target_link_libraries(raytracer PUBLIC trace)

add_executable(colortest
    test/colors.cpp
    )

target_link_libraries(colortest PUBLIC trace)
