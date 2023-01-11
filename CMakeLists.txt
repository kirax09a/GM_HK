cmake_minimum_required(VERSION 3.16)
project(curve_approximation)

set(CMAKE_CXX_STANDARD 14)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(libigl)

igl_include(glfw)

# add source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# add header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)



add_library(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
add_library(approximation ALIAS ${PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw)