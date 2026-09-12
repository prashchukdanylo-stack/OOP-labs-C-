cmake_minimum_required(VERSION 3.16)
project(Sigma LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Lab1
 main.cpp
 module1.h
 module1.cpp
 module2.h
 module2.cpp
 mainwindow.h
 mainwindow.cpp
 )

target_link_libraries(Lab1 PRIVATE Qt6::Widgets)