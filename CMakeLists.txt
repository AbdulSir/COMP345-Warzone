cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Resources)
find_package(Boost 1.68 REQUIRED)
add_executable(MapDriver MapDriver.cpp Map.cpp)
target_link_libraries(MapDriver PUBLIC Boost::boost)

add_executable(CardsDriver CardsDriver.cpp Cards.cpp)
add_executable(PlayerDriver PlayerDriver.cpp Player.cpp)
# add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
add_executable(GameEngine GameEngineDriver.cpp GameEngine.cpp)