#pragma once

#include "HospitalDepartment.h"
#include <string>

class Surgery: public HospitalDepartment
{
private:
    int numberOfPatients;

public:
    Surgery(std::string hopitalName, int numberOfDoctors, int numberOfPatients);
    ~Surgery();

    virtual bool IsEfficient() override;
    virtual std::string ToString() override;
};
