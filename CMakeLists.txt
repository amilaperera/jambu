cmake_minimum_required (VERSION 3.8)
project(jambu)

add_executable(incremental_id_generator_tests test/incremental_id_generator_tests.cpp)

target_compile_features(incremental_id_generator_tests PRIVATE cxx_std_17)

