#pragma once

#include <string>
#include <vector>
#include "Serializable.h"

class Material : public Serializable
{
private:
    std::string id;
    std::string size;
    float infectionLevel;
    int microfragmentsQuantity;
    std::string photograph;

public:
    Material();
    Material(std::string id, std::string size, float infectionLevel, int microfragmentsQuantity, std::string photograph);
    Material(const Material &source);
    ~Material();

    Material& operator=(Material const& source);
    friend std::ostream& operator<< (std::ostream& outStream, Material const& material);
    friend std::istream& operator>> (std::istream& inStream, Material& material);

    std::string Id() const;
    std::string Size() const;
    float InfectionLevel() const;
    int MicrofragmentsQuantity() const;
    std::string Photograph() const;

    // Inherited via Serializable
    virtual std::vector<std::string> Serialize() override;
    virtual void Deserialize(std::vector<std::string> tokens) override;
};

