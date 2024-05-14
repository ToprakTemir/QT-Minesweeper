cmake_minimum_required(VERSION 3.27)
project(MineSweeper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/toprak/Qt/6.7.0/macos/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(MineSweeper main.cpp
        Labels.h
        Labels.cpp
        MineGrid.cpp
        Cell.cpp)
target_link_libraries(MineSweeper
        Qt::Core
        Qt::Gui
        Qt::Widgets
)