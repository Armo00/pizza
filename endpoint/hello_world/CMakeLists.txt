add_executable(hello_world src/hello_world.cpp src/entry.cpp)
target_link_libraries(hello_world ${CONAN_LIBS})
