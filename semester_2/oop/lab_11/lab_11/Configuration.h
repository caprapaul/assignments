#pragma once

#include <map>
#include <string>

class Configuration
{
private:
    std::string filePath;
    std::map<std::string, std::string> configuration;

public:
    Configuration(std::string filePath);

    void save();
    void load();

    std::string get(std::string key);
    void set(std::string key, std::string newValue);
};

