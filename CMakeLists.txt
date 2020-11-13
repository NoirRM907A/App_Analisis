cmake_minimum_required(VERSION 3.17)
project(App_Analisis)

set(CMAKE_CXX_STANDARD 14)

add_executable(App_Analisis Main/main.cpp Interfaz/Interfaz.h Entidades/Paciente.cpp Entidades/Paciente.h Entidades/Enfermedad.cpp Entidades/Enfermedad.h json.hpp Programa/Programa.cpp Programa/Programa.h)