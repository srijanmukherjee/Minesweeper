cmake_minimum_required(VERSION 3.0)
project(MineSweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(MineSweeper main.cpp game/Game.cpp game/Game.h game/Board.cpp game/Board.h game/Cell.cpp game/Cell.h game/Asset.cpp game/Asset.h game/CellMeta.h)

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MineSweeper sfml-graphics sfml-audio)
endif()

# set(SFML_STATIC_LIBRARIES TRUE)
