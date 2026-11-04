cmake_minimum_required(VERSION 3.16)
project(Lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(
    Lab5
    main.cpp
    mainWindow.cpp
    myEditor.cpp
    shape.cpp
    myTable.cpp
    resources.qrc
 )

target_link_libraries(Lab5 PRIVATE Qt6::Widgets)