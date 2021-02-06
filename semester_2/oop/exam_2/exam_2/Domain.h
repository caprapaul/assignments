#pragma once

#include <string>
#include <vector>

#include "Serializable.h"

class Domain : public Serializable
{
private:
    std::string manufacturer;
    std::string model;
    int fabricationYear;
    std::string color;

public:
    Domain();
    Domain(std::string manufacturer, std::string model, int fabricationYear, std::string color);
    ~Domain();

    std::string Manufacturer();
    std::string Model();
    int FabricationYear();
    std::string Color();

    // Inherited via Serializable
    virtual std::vector<std::string> Serialize() override;
    virtual void Deserialize(std::vector<std::string> tokens) override;
};

