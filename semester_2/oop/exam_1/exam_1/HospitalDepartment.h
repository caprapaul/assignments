#pragma once

#include <string>

class HospitalDepartment
{
protected:
    std::string hospitalName;
    int numberOfDoctors;

public:
    HospitalDepartment();
    HospitalDepartment(std::string hopitalName, int numberOfDoctors);

    virtual bool IsEfficient();
    virtual std::string ToString();
};
