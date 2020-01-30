cmake_minimum_required (VERSION 3.8)
project(jambu)

add_executable(tests test/tests.cpp)
target_compile_features(tests PRIVATE cxx_std_17)

