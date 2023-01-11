cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 14)

include(libigl)

igl_include(glfw)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC approximation)
