#pragma once
#include "RepositoryFile.h"
#include <fstream>
#include <algorithm>
#include <sstream>

template <typename TElement>
class RepositoryHTML : public RepositoryFile<TElement>
{
private:
    int serializedSize;
    std::string title;
    std::vector<std::string> headers;

    std::vector<TElement> loadFromFile();
    void saveToFile(std::vector<TElement> elements);
    std::string addTd(std::string input);
    std::string trimTd(std::string input);

public:
    RepositoryHTML(std::string title, std::vector<std::string> headers);
    RepositoryHTML(RepositoryHTML const& repository);
    ~RepositoryHTML();
};

template <typename TElement>
std::vector<TElement> RepositoryHTML<TElement>::loadFromFile()
{
    std::ifstream file(this->filePath);
    std::vector<TElement> elements;
    TElement element;

    std::vector<string> lines;

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    if (lines.size() == 0)
    {
        return elements;
    }

    for (size_t i = 14; i < lines.size() - 3; i += this->serializedSize + 2)
    {
        std::vector<std::string> tokens;

        for (size_t column = 0; column < this->serializedSize; column++)
        {
            tokens.push_back(this->trimTd(lines[i + column + 1]));
        }

        TElement element;
        element.Deserialize(tokens);

        elements.push_back(element);
    }

    return elements;
}

template <typename TElement>
void RepositoryHTML<TElement>::saveToFile(std::vector<TElement> elements)
{
    ofstream file(this->filePath, ofstream::trunc);

    string output = "<!DOCTYPE html>\n";
    output += "<html>\n";
    output += "\t<head>\n";
    output += "\t\t<title>" + this->title + "</title>\n";
    output += "\t</head>\n";
    output += "\t<body>\n";
    output += "\t\t<table border=\"1\">\n";

    output += "\t\t<tr>\n";
    
    for (auto header : this->headers)
    {
        output += this->addTd(header);
    }

    output += "\t\t</tr>\n";

    for (auto element : elements)
    {
        output += "\t\t<tr>\n";

        std::vector<std::string> tokens = element.Serialize();

        for (auto token : tokens)
        {
            output += this->addTd(token);
        }

        output += "\t\t</tr>\n";
    }

    output += "\t\t</table>\n";
    output += "\t</body>\n";
    output += "</html>\n";

    file << output;

    file.close();
}

template<typename TElement>
inline std::string RepositoryHTML<TElement>::addTd(std::string input)
{
    return "\t\t\t<td>" + input + "</td>\n";
}

template <typename TElement>
std::string RepositoryHTML<TElement>::trimTd(std::string input)
{
    std::string subString = input.substr(7);
    std::stringstream subStringStream(subString);

    std::string trimmed;
    std::getline(subStringStream, trimmed, '<');

    return trimmed;
}

template <typename TElement>
RepositoryHTML<TElement>::RepositoryHTML(std::string title, std::vector<std::string> headers)
{
    this->title = title;
    this->headers = headers;
    this->serializedSize = headers.size();
}

template <typename TElement>
RepositoryHTML<TElement>::RepositoryHTML(RepositoryHTML const& repository)
{
}

template <typename TElement>
RepositoryHTML<TElement>::~RepositoryHTML()
{
}
