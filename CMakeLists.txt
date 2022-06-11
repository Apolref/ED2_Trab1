cmake_minimum_required(VERSION 3.21)
project(T1temp)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        contagem_intersecoes.h
        CtrlF.h
        matriz.h
        Ordena.h
        )

set(PROJECT_SOURCES
        main.c
        contagem_intersecoes.c
        CtrlF.c
        matriz.c
        Ordena.c
        )

add_executable(T1temp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
