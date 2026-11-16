cmake_minimum_required(VERSION 3.16)
project(Lab6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 1. Головна програма-менеджер Lab6
add_executable(
    Lab6
    Lab6.cpp
    MainWindow.cpp
    SettingsDialog.cpp
    MainWindow.h
    SettingsDialog.h
)
target_link_libraries(Lab6 PRIVATE Qt6::Widgets)

# 2. Програма генерації даних Object2
add_executable(
    Object2
    Object2.cpp
    Object2Window.cpp
    Object2Window.h
)
target_link_libraries(Object2 PRIVATE Qt6::Widgets)

# 3. Програма побудови графіка Object3
add_executable(
    Object3
    Object3.cpp
    Object3Window.cpp
    Object3Window.h
    GraphWidget.cpp
    GraphWidget.h
)
target_link_libraries(Object3 PRIVATE Qt6::Widgets)