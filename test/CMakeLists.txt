project(hello_tests)

# The test program
add_executable(tests testmain.cpp)
target_link_libraries(tests PRIVATE hello_lib catch)
target_compile_definitions(tests PRIVATE CATCH_CONFIG_CONSOLE_WIDTH=60)
