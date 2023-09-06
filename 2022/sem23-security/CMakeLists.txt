cmake_minimum_required(VERSION 3.14)
project(inf22_0 C)

find_package(OpenSSL REQUIRED)

set(CMAKE_C_STANDARD 99)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(main main.c)

target_link_libraries(main ${OPENSSL_CRYPTO_LIBRARY})
