cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

find_package(Boost 1.68 REQUIRED)
add_executable(MapDriver MapDriver.cpp Map.cpp)
target_link_libraries(MapDriver PUBLIC Boost::boost)

add_executable(CardsDriver CardsDriver.cpp Cards.cpp)
# add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
