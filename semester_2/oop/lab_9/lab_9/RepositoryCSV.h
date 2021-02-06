#pragma once
#include "RepositoryFile.h"
#include "Material.h"
#include "Utility.h"
#include <fstream>

class RepositoryCSV : public RepositoryFile<Material>
{
private:
    std::vector<Material> loadFromFile();
    void saveToFile(std::vector<Material> elements);

public:
    RepositoryCSV();
    RepositoryCSV(RepositoryCSV const& repository);
    ~RepositoryCSV();

};
