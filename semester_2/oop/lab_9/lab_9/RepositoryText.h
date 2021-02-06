#pragma once
#include "RepositoryFile.h"
#include "Material.h"
#include <fstream>
#include <algorithm>

class RepositoryText : public RepositoryFile<Material>
{
private:
    std::vector<Material> loadFromFile();
    void saveToFile(std::vector<Material> elements);

public:
    RepositoryText();
    RepositoryText(RepositoryText const& repository);
    ~RepositoryText();
};
