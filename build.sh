#!/bin/bash

# Eliminar y recrear el directorio build
rm -rf build
mkdir -p build
cd build

# Configurar y compilar
cmake ..
make

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa"
    # Ejecutar
    ./CortexEngine
else
    echo "Error en la compilación"
    exit 1
fi