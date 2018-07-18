cmake_minimum_required(VERSION 3.6)

# The project name
project(hello_cmake)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(thirdparty/catch)
add_subdirectory(src)
add_subdirectory(test)
