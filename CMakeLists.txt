cmake_minimum_required(VERSION 3.16)

project(HW3D)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(HW3D
    src/main.cpp
    third_party/glad/src/glad.c
    src/render/Shaders.cpp
    src/render/Camera.cpp
    src/render/Geometry.cpp
    src/geometry/Intersection.cpp
    src/geometry/Grid.cpp
    src/geometry/Test.cpp
)

target_include_directories(HW3D PRIVATE
    src
    third_party/glad/include
)

target_link_libraries(HW3D
    OpenGL::GL
    glfw
    glm::glm
)