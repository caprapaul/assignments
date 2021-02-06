#include "Surgery.h"


using namespace std;

Surgery::Surgery(std::string hopitalName, int numberOfDoctors, int numberOfPatients)
{
    this->hospitalName = hopitalName;
    this->numberOfDoctors = numberOfDoctors;
    this->numberOfPatients = numberOfPatients;
}

Surgery::~Surgery()
{
}

bool Surgery::IsEfficient()
{
    return numberOfPatients / numberOfDoctors >= 2;
}

std::string Surgery::ToString()
{
    return this->hospitalName + " " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfPatients) + " " + to_string(this->IsEfficient());
}
