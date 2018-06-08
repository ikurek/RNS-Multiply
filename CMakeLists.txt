cmake_minimum_required(VERSION 3.10)
project(RNS_Multiply)

set(CMAKE_CXX_STANDARD 11)

add_executable(RNS_Multiply main.cpp Conversions.cpp Conversions.h MRNMultiply.cpp MRNMultiply.h)