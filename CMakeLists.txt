cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

add_executable(CardDriver CardsDriver.cpp)

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
