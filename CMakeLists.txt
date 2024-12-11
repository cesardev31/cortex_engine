cmake_minimum_required(VERSION 3.10)
project(CortexEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Encontrar OpenGL
find_package(OpenGL REQUIRED)

# Configurar política de OpenGL GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Encontrar SQLite3
find_package(SQLite3 REQUIRED)

# Archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

# Ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Vincular bibliotecas
target_link_libraries(${PROJECT_NAME} 
    sfml-system 
    sfml-window 
    sfml-graphics
    OpenGL::GL
    SQLite::SQLite3
)

# Incluir directorios de cabecera
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

# Copiar recursos
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
)