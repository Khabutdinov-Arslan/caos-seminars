cmake_minimum_required(VERSION 3.13)
project(fuse_demo C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3) # apt install libfuse3-dev pkg-config fuse3

link_libraries(${FUSE_LIBRARIES})         # -lfuse3 -lpthread
include_directories(${FUSE_INCLUDE_DIRS}) # -I/usr/include/fuse3
# compile_options(${FUSE_CFLAGS_OTHER})     # empty since fuse 3.0

add_executable(fuse_demo main.c)
