#include "ProjectRepository.hpp"

namespace Infrastructure
{
    ProjectRepository::ProjectRepository()
    {
        dbPath = getDatabasePath();
        initializeDatabase();
    }

    ProjectRepository::~ProjectRepository()
    {
        // Implementación del destructor
    }

    void ProjectRepository::initializeDatabase()
    {
        int rc = sqlite3_open(dbPath.string().c_str(), &db);
        if (rc)
        {
            throw std::runtime_error("No se pudo abrir la base de datos");
        }

        const char *sql = R"(
            CREATE TABLE IF NOT EXISTS projects (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                path TEXT UNIQUE NOT NULL,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                last_opened DATETIME DEFAULT CURRENT_TIMESTAMP
            );
        )";

        char *errMsg = nullptr;
        rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK)
        {
            std::string error = errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error("Error al crear tabla: " + error);
        }
    }

    bool ProjectRepository::addProject(const Domain::ProjectInfo &project)
    {
        const char *sql = R"(
            INSERT OR REPLACE INTO projects (name, path, last_opened)
            VALUES (?, ?, CURRENT_TIMESTAMP);
        )";

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
            return false;

        sqlite3_bind_text(stmt, 1, project.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, project.getPath().string().c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return rc == SQLITE_DONE;
    }

    std::vector<Domain::ProjectInfo> ProjectRepository::getRecentProjects(int limit)
    {
        std::vector<Domain::ProjectInfo> projects;
        const char *sql = R"(
            SELECT name, path FROM projects 
            ORDER BY last_opened DESC LIMIT ?;
        )";

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
            return projects;

        sqlite3_bind_int(stmt, 1, limit);

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            std::string path = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            projects.emplace_back(name, path);
        }

        sqlite3_finalize(stmt);
        return projects;
    }

    std::filesystem::path ProjectRepository::getDatabasePath()
    {
        std::filesystem::path userHome = std::getenv("HOME") ? std::getenv("HOME") : std::getenv("USERPROFILE");
        std::filesystem::path dbDir = userHome / ".cortex";

        // Crear el directorio si no existe
        if (!std::filesystem::exists(dbDir))
        {
            std::filesystem::create_directory(dbDir);
        }

        return dbDir / "projects.db";
    }
}