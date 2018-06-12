project(Hello_prog)

# All sources that also need to be tested in unit tests go into a static library
add_library(hello_lib STATIC hello.cpp hello.h)
target_include_directories(hello_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(prog main.cpp)
target_link_libraries(prog PRIVATE hello_lib)

