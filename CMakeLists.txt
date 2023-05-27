cmake_minimum_required(VERSION 3.24)
project(garden)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/CMAKE_DEPS")

find_package( botan 3.0.0  REQUIRED )
botan_generate(botan system_rng argon2 sha3 compression hash argon2fmt block stream aead)

find_package( imgui 3.0.0 REQUIRED)

find_package( cereal 1.3.2 REQUIRED)

add_executable(garden main.cpp file/file.cpp file/file.h file/format.h misc/types.h)
target_link_libraries(garden PRIVATE botan)
target_link_libraries(garden PRIVATE cereal)