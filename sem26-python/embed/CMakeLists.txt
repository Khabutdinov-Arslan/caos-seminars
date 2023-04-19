cmake_minimum_required(VERSION 3.13)
project(main C)

add_executable(main main.c)

find_package(PythonLibs 3.6 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(main ${PYTHON_LIBRARIES})

