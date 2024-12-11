#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <nlohmann/json.hpp>
#include "../../domain/entities/Project.hpp"
#include "../../infrastructure/storage/ProjectRepository.hpp"

using json = nlohmann::json;

class ProjectManager
{
private:
    Infrastructure::ProjectRepository projectRepo;

    bool createProjectStructure(const std::filesystem::path &projectPath)
    {
        try
        {
            // Crear directorio principal del proyecto
            std::filesystem::create_directories(projectPath);

            // Crear estructura básica de carpetas
            std::filesystem::create_directories(projectPath / "assets");
            std::filesystem::create_directories(projectPath / "scenes");
            std::filesystem::create_directories(projectPath / "scripts");
            std::filesystem::create_directories(projectPath / "resources");

            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al crear la estructura del proyecto: " << e.what() << std::endl;
            return false;
        }
    }

    bool createProjectConfig(const Domain::ProjectInfo &project)
    {
        try
        {
            json config = {
                {"name", project.getName()},
                {"version", "1.0.0"},
                {"created_at", std::chrono::system_clock::to_time_t(project.getCreatedAt())},
                {"engine_version", "0.1.0"},
                {"settings", {{"resolution", {{"width", 800}, {"height", 600}}}, {"fps", 60}, {"vsync", true}}}};

            std::filesystem::path configPath = project.getPath() / "project.cortex";
            std::ofstream o(configPath);
            o << std::setw(4) << config << std::endl;
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al crear el archivo de configuración: " << e.what() << std::endl;
            return false;
        }
    }

public:
    bool createProject(const std::string &name, const std::filesystem::path &path)
    {
        try
        {
            // Verificar si el directorio ya existe
            if (std::filesystem::exists(path))
            {
                throw std::runtime_error("El directorio ya existe");
            }

            // Crear el objeto ProjectInfo
            Domain::ProjectInfo project(name, path);

            // Crear la estructura de carpetas
            if (!createProjectStructure(path))
            {
                return false;
            }

            // Crear el archivo de configuración
            if (!createProjectConfig(project))
            {
                // Limpiar los directorios creados en caso de error
                std::filesystem::remove_all(path);
                return false;
            }

            // Registrar el proyecto en la base de datos
            if (!projectRepo.addProject(project))
            {
                // Limpiar los directorios creados en caso de error
                std::filesystem::remove_all(path);
                return false;
            }

            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al crear el proyecto: " << e.what() << std::endl;
            return false;
        }
    }
};