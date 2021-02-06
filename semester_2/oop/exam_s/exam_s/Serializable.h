#pragma once

#include <vector>
#include <string>

class Serializable
{
public:
    virtual ~Serializable() {};

    virtual std::vector<std::string> Serialize() = 0;
    virtual void Deserialize(std::vector<std::string> tokens) = 0;
};

