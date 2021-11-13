cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Resources)
find_package(Boost 1.68 REQUIRED)

add_executable(MapDriver MapDriver.cpp Player.cpp Orders.cpp Cards.cpp Map.cpp)
target_link_libraries(MapDriver PUBLIC Boost::boost)

# add_executable(PlayerDriver PlayerDriver.cpp Player.cpp)
# add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
add_executable(GameEngine GameEngineDriver.cpp GameEngine.cpp)

add_executable(Part4Demo Part4Demo.cpp Player.cpp Orders.cpp Cards.cpp Map.cpp)
add_executable(OrdersDriver OrdersDriver.cpp Orders.cpp)

add_executable(CommandProcessingDriver CommandProcessingDriver.cpp CommandProcessing.cpp)
