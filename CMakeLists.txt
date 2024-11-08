cmake_minimum_required(VERSION 3.15)
project(let_me_cook C)

set(CMAKE_C_STANDARD 11)  # O la versión de C que estés usando

# Agrega todos los archivos fuente de tu proyecto aquí
add_executable(let_me_cook main.c articulos.c ventas.c manejoArchivos.c
        empleados.h
        manejoArchivos.h
        provedor.h
        insumos.h
        empleados.c
        insumos.c
        reportes.h
        reportes.c
        provedor.c)
