cmake_minimum_required(VERSION 3.10)
project(BusEscape VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(BusEscape
    src/Objeto.cpp
    src/Vehiculo.cpp
    src/Persona.cpp
    src/MNivel.cpp
    src/CJuego.cpp
    src/VDisplay.cpp
    src/main.cpp
)

target_include_directories(BusEscape PRIVATE ${CMAKE_SOURCE_DIR}/niveles)
