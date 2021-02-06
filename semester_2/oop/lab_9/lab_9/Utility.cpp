#include "Utility.h"

#include <sstream>

using namespace std;

std::vector<std::string> Utility::splitString(std::string input, char delimiter)
{
    vector<string> tokens;

    stringstream inputStringStream(input);

    while (inputStringStream.good())
    {
        string subString;
        getline(inputStringStream, subString, delimiter);
        tokens.push_back(subString);
    }

    return tokens;
}

bool Utility::isNumber(std::string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (isdigit(input[i]) == false)
        {
            return false;
        }
    }

    return true;
}

std::string Utility::getFileExtension(std::string filePath)
{
    size_t foundIndex = filePath.rfind('.', filePath.length());

    if (foundIndex != string::npos)
    {
        return filePath.substr(foundIndex + 1, filePath.length() - foundIndex);
    }

    return "";
}
