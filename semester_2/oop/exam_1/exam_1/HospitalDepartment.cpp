#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment()
{
    this->hospitalName = "";
    this->numberOfDoctors = 0;
}

HospitalDepartment::HospitalDepartment(std::string hopitalName, int numberOfDoctors)
{
    this->hospitalName = hopitalName;
    this->numberOfDoctors = numberOfDoctors;
}

bool HospitalDepartment::IsEfficient()
{
    return false;
}

std::string HospitalDepartment::ToString()
{
    return this->hospitalName + " " + std::to_string(this->numberOfDoctors);
}
