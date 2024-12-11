#!/bin/bash

mkdir -p build
cd build

# Compilar los archivos fuente individuales
g++ -c ../src/infrastructure/storage/ProjectRepository.cpp -I../src
g++ -c ../src/main.cpp -I../src

# Enlazar todos los objetos en el ejecutable final
g++ ProjectRepository.o main.o -o cortex -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

# Ejecutar el programa desde build
./cortex