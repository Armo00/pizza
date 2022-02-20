add_executable(hello_world src/hello_world.cpp src/entry.cpp)
target_link_libraries(hello_world ${CONAN_LIBS})

add_executable(db_demo src/demo/db_demo.cpp)
target_link_libraries(db_demo ${CONAN_LIBS})

add_executable(hash_demo src/demo/hash_demo.cpp)
target_link_libraries(hash_demo ${CONAN_LIBS})
