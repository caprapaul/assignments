#include "Configuration.h"

#include <fstream>
#include <vector>
#include "Utility.h"
using namespace std;

Configuration::Configuration(std::string filePath)
{
    this->filePath = filePath;
}

void Configuration::save()
{
    ofstream file(this->filePath);

    for (auto configurationItem : this->configuration)
    {
        file << configurationItem.first << "=" << configurationItem.second;
    }

    file.close();
}

void Configuration::load()
{
    ifstream file(this->filePath);
    string line;
    while (getline(file, line))
    {
        vector<string> lineTokens = Utility::splitString(line, '=');
        this->configuration[lineTokens[0]] = lineTokens[1];
    }

    file.close();
}

string Configuration::get(string key)
{
    return this->configuration[key];
}

void Configuration::set(string key, string newValue)
{
    this->configuration[key] = newValue;
}
