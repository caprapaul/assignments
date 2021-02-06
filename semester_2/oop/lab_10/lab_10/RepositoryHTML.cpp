#include "RepositoryHTML.h"

#include <sstream>
using namespace std;

vector<Material> RepositoryHTML::loadFromFile()
{
    ifstream file(this->filePath);
    vector<Material> elements;
    Material element;

    vector<string> lines;

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    if (lines.size() == 0)
    {
        return elements;
    }

    for (size_t i = 14; i < lines.size() - 3; i += 7)
    {
        vector<string> tokens{
            this->trimTd(lines[i + 1]),
            this->trimTd(lines[i + 2]),
            this->trimTd(lines[i + 3]),
            this->trimTd(lines[i + 4]),
            this->trimTd(lines[i + 5])
        };

        Material element(tokens);
        elements.push_back(element);
    }

    return elements;
}

void RepositoryHTML::saveToFile(vector<Material> elements)
{
    ofstream file(this->filePath, ofstream::trunc);

    string output = "<!DOCTYPE html>\n";
    output += "<html>\n";
    output += "\t<head>\n";
    output += "\t\t<title>Saved Materials</title>\n";
    output += "\t</head>\n";
    output += "\t<body>\n";
    output += "\t\t<table border=\"1\">\n";

    output += "\t\t<tr>\n";
    output += "\t\t\t<td>" + string("Id") + "</td>\n";
    output += "\t\t\t<td>" + string("Size") + "</td>\n";
    output += "\t\t\t<td>" + string("Infection Level") + "</td>\n";
    output += "\t\t\t<td>" + string("Microfragments Quantity") + "</td>\n";
    output += "\t\t\t<td>" + string("Photograph") + "</td>\n";
    output += "\t\t</tr>\n";

    for (auto material : elements)
    {
        output += "\t\t<tr>\n";
        output += "\t\t\t<td>" + material.Id() + "</td>\n";
        output += "\t\t\t<td>" + material.Size() + "</td>\n";
        output += "\t\t\t<td>" + to_string(material.InfectionLevel()) + "</td>\n";
        output += "\t\t\t<td>" + to_string(material.MicrofragmentsQuantity()) + "</td>\n";
        output += "\t\t\t<td>" + material.Photograph() + "</td>\n";
        output += "\t\t</tr>\n";
    }

    output += "\t\t</table>\n";
    output += "\t</body>\n";
    output += "</html>\n";

    file << output;

    file.close();
}

std::string RepositoryHTML::trimTd(std::string input)
{
    string subString = input.substr(7);
    stringstream subStringStream(subString);

    string trimmed;
    getline(subStringStream, trimmed, '<');

    return trimmed;
}


RepositoryHTML::RepositoryHTML()
{
}


RepositoryHTML::RepositoryHTML(RepositoryHTML const& repository)
{
}


RepositoryHTML::~RepositoryHTML()
{
}
