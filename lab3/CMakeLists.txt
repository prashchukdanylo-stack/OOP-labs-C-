cmake_minimum_required(VERSION 3.16)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(
    Lab3
    main.cpp
    mainWindow.cpp
    shape.cpp
    resources.qrc
 )

target_link_libraries(Lab3 PRIVATE Qt6::Widgets)