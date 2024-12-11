#pragma once
#include <vector>
#include <sqlite3.h>
#include "../../domain/entities/Project.hpp"

namespace Infrastructure
{
    class ProjectRepository
    {
    private:
        sqlite3 *db;
        std::filesystem::path dbPath;

    public:
        ProjectRepository();
        virtual ~ProjectRepository();

        bool addProject(const Domain::ProjectInfo &project);
        std::vector<Domain::ProjectInfo> getRecentProjects(int limit);
        bool updateLastOpened(const std::filesystem::path &path);
        bool removeProject(const std::filesystem::path &path);
        bool exists(const std::filesystem::path &path);

    private:
        void initializeDatabase();
        static std::filesystem::path getDatabasePath();
    };
}
