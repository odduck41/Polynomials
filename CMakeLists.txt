cmake_minimum_required(VERSION 3.28)
project(Polynomials)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/cmake/Qt6")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(Polynomials src/main.cpp
        include/Polynomial.h
        src/Polynomial.cpp
        include/Window.h
        src/Window.cpp
        include/DataBase.h
        src/DataBase.cpp
        include/List.h
        include/StateMachine.h
        src/StateMachine.cpp
        src/StateMachine.cpp
        include/logger.h
        src/logger.cpp
)

target_link_libraries(Polynomials PRIVATE Qt6::Widgets)
