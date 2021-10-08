cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

add_executable(CardsDriver CardsDriver.cpp Cards.cpp)
add_executable(PlayerDriver PlayerDriver.cpp Player.cpp)
# add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
add_executable(GameEngine GameEngineDriver.cpp GameEngine.cpp)