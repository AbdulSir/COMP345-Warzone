cmake_minimum_required(VERSION 3.16.3)

project(WARZONE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Resources)
find_package(Boost 1.68 REQUIRED)

add_executable(Part1Demo Part1Demo.cpp PlayerStrategies.cpp Player.cpp Orders.cpp Cards.cpp Map.cpp LoggingObserver.cpp GameEngine.cpp)
# add_executable(Part3Demo Part3Demo.cpp GameEngine.cpp LoggingObserver.cpp CommandProcessing.cpp Player.cpp Orders.cpp Cards.cpp Map.cpp)
# add_executable(Part4Demo Part4Demo.cpp Player.cpp LoggingObserver.cpp Orders.cpp Cards.cpp Map.cpp)
# add_executable(Part5Demo LoggingObserverDriver.cpp LoggingObserver.cpp GameEngine.cpp CommandProcessing.cpp Player.cpp Orders.cpp Cards.cpp Map.cpp)
# target_link_libraries(Part2Demo PUBLIC Boost::boost)
# target_link_libraries(Part4Demo PUBLIC Boost::boost)
# target_link_libraries(Part5Demo PUBLIC Boost::boost)

# add_executable(CommandProcessingDriver CommandProcessingDriver.cpp CommandProcessing.cpp GameEngine.cpp)
