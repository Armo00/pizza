cmake_minimum_required(VERSION 3.22)
project("restapi-cxx")

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Werror=all -Werror=extra -Wdocumentation -Wfatal-errors)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
add_compile_definitions(CRYPTOPP_ENABLE_NAMESPACE_WEAK)
conan_basic_setup()

include_directories(library/include)
file(GLOB endpoints "endpoint/*")

foreach(endpoint ${endpoints})
  if(IS_DIRECTORY ${endpoint})
    message("-- Detected endpoint directory: ${endpoint}")
    add_subdirectory(${endpoint})
  endif()
endforeach()

if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scratch)
  message("-- Scratch directory detected")
  add_subdirectory(scratch)
endif()
