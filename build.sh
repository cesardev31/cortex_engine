#!/bin/bash

# Crear y entrar al directorio build
mkdir -p build
cd build

# Configurar y compilar
cmake ..
make

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    # Ejecutar
    ./CortexEngine
else
    echo "Error en la compilación"
    exit 1
fi