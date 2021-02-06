#include "Controller.h"

using namespace std;

Controller::Controller()
{
}

Controller::Controller(Repository<std::shared_ptr<HospitalDepartment>> repository)
{
}

Controller::~Controller()
{
}

void Controller::AddDepartment(std::shared_ptr<HospitalDepartment> department)
{
    this->repository.Add(department);
}

std::vector<HospitalDepartment> Controller::GetAllDepartments()
{
    vector<HospitalDepartment> departments;
    vector<shared_ptr<HospitalDepartment>> ptrDepartments = this->repository.GetAll();

    for (int i = 0; i < ptrDepartments.size(); i++)
    {
        HospitalDepartment department = *ptrDepartments[i];
        departments.push_back(department);
    }

    return departments;
}

std::vector<HospitalDepartment> Controller::GetAllEfficientDepartments()
{
    vector<HospitalDepartment> departments;
    vector<shared_ptr<HospitalDepartment>> ptrDepartments = this->repository.GetAll();

    for (int i = 0; i < ptrDepartments.size(); i++)
    {
        HospitalDepartment department = *ptrDepartments[i];

        if (department.IsEfficient())
        {
            departments.push_back(department);
        }
    }

    return departments;
}

void Controller::WriteToFile(std::string filePath)
{
    vector<shared_ptr<HospitalDepartment>> ptrDepartments = this->repository.GetAll();
    std::ofstream file(filePath);

    int elementIndex = 0;
    for (auto departmentPtr : ptrDepartments)
    {
        HospitalDepartment department = *departmentPtr;

        file << department.ToString();

        if (elementIndex < ptrDepartments.size() - 1)
        {
            file << std::endl;
        }

        elementIndex++;
    }

    file.close();
}
