cmake_minimum_required(VERSION 3.22)
project("restapi-cxx")

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD 20)
# remove no-error=documentation as soon as
# https://github.com/pistacheio/pistache/issues/1038 is fixed
add_compile_options(-Wall -Wextra -Wdocumentation -Werror
                    -Wno-error=documentation)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
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
