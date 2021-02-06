#pragma once

#include "RepositoryText.h"
#include "HospitalDepartment.h"

class Controller
{
private:
    Repository<std::shared_ptr<HospitalDepartment>> repository;

public:
    Controller();
    Controller(Repository<std::shared_ptr<HospitalDepartment>> repository);
    ~Controller();

    void AddDepartment(std::shared_ptr<HospitalDepartment> department);
    std::vector<HospitalDepartment> GetAllDepartments();
    std::vector<HospitalDepartment> GetAllEfficientDepartments();
    void WriteToFile(std::string filePath);
};
