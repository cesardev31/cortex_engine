#pragma once
#include <string>
#include <filesystem>
#include <chrono>

namespace Domain
{
    class ProjectInfo
    {
    private:
        std::string name;
        std::filesystem::path path;
        std::chrono::system_clock::time_point createdAt;

    public:
        ProjectInfo(const std::string &projectName, const std::filesystem::path &projectPath)
            : name(projectName), path(projectPath), createdAt(std::chrono::system_clock::now())
        {
        }

        const std::string &getName() const { return name; }
        const std::filesystem::path &getPath() const { return path; }
        const auto &getCreatedAt() const { return createdAt; }
    };
}
