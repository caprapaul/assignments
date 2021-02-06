#pragma once

#include <string>
#include <vector>

class Utility
{
public:
    static std::vector<std::string> splitString(std::string input, char delimiter);
    static bool isNumber(std::string input);
    static std::string getFileExtension(std::string filePath);
};

