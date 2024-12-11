cmake_minimum_required(VERSION 3.10)
project(CortexEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Encontrar SQLite3
find_package(SQLite3 REQUIRED)

# Archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

# Ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Vincular SFML
target_link_libraries(${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system
    SQLite::SQLite3
)

# Copiar recursos (corregido)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
)