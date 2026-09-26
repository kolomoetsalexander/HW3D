cmake_minimum_required(VERSION 3.16)

project(HW3D)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HW3D
    main.cpp
    glad/src/glad.c
)

target_include_directories(HW3D PRIVATE
    glad/include
)

target_link_libraries(HW3D
    OpenGL::GL
    glfw
)