#pragma once
#include "RepositoryFile.h"
#include "Material.h"
#include <fstream>
#include <algorithm>

class RepositoryHTML : public RepositoryFile<Material>
{
private:
    std::vector<Material> loadFromFile();
    void saveToFile(std::vector<Material> elements);
    std::string trimTd(std::string input);

public:
    RepositoryHTML();
    RepositoryHTML(RepositoryHTML const& repository);
    ~RepositoryHTML();
};
