cmake_minimum_required (VERSION 3.8)
project(jambu)

add_executable(tests test/main.cpp)

target_compile_features(tests PRIVATE cxx_std_17)

