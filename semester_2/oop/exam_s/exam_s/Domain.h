#pragma once

#include <string>
#include <vector>

#include "Serializable.h"

class Domain : public Serializable
{
private:
    std::string name;
    std::string constellation;
    int rightAscension;
    int declination;
    int diameter;

public:
    Domain();
    Domain(std::string name, std::string constellation, int rightAscension, int declination, int diameter);
    ~Domain();

    std::string Name();
    std::string Constellation();
    int RA();
    int Dec();
    int Diameter();

    // Inherited via Serializable
    virtual std::vector<std::string> Serialize() override;
    virtual void Deserialize(std::vector<std::string> tokens) override;
};

