#pragma once
#include <string>
#include <vector>

#include "Serializable.h"

class Astronomer: public Serializable
{
private:
    std::string name;
    std::string constellation;

public:
    Astronomer();
    Astronomer(std::string name, std::string constellation);
    ~Astronomer();

    std::string Name();
    std::string Constellation();

    // Inherited via Serializable
    virtual std::vector<std::string> Serialize() override;
    virtual void Deserialize(std::vector<std::string> tokens) override;

};

