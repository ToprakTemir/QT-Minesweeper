cmake_minimum_required(VERSION 3.27)
project(QT_Minesweeper)

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

add_executable(QT_Minesweeper main.cpp
        Labels.h
        Labels.cpp
        MineGrid.h
        Cell.h
        MineGrid.cpp
        Cell.cpp)
target_link_libraries(QT_Minesweeper
        Qt::Core
        Qt::Gui
        Qt::Widgets
)