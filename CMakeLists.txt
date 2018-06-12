cmake_minimum_required(VERSION 3.6)

# The project name
project(hello_cmake)

add_subdirectory(thirdparty/catch)

# The sources shared between the main program and the tests
set (PROJECT_SOURCES hello.cpp hello.h)

# The main program
add_executable(prog main.cpp ${PROJECT_SOURCES})

# The tests
add_executable(tests testmain.cpp ${PROJECT_SOURCES})
target_link_libraries(tests PRIVATE catch)
