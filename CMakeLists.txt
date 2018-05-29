set (PROJECT_SOURCES hello.cpp hello.h)

add_executable(prog main.cpp ${PROJECT_SOURCES})

add_executable(tests testmain.cpp ${PROJECT_SOURCES})
