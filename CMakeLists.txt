cmake_minimum_required(VERSION 3.6)

# The project name
project(hello_cmake)

add_subdirectory(thirdparty/catch)
add_subdirectory(src)
add_subdirectory(test)

