#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

class EventSystem
{
private:
    std::map<std::string, std::vector<std::function<void(void *)>>> handlers;

public:
    void subscribe(const std::string &event, std::function<void(void *)> handler)
    {
        handlers[event].push_back(handler);
    }

    void emit(const std::string &event, void *data = nullptr)
    {
        if (handlers.find(event) != handlers.end())
        {
            for (auto &handler : handlers[event])
            {
                handler(data);
            }
        }
    }
};