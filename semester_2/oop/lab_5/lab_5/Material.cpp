#include "Material.h"

#include <iostream>
using namespace std;

Material::Material()
{
    this->id = "";
    this->size = "0X0X0";
    this->infectionLevel = 0.0;
    this->microfragmentsQuantity = 0;
    this->photograph = "";
}

Material::Material(string id, string size, float infectionLevel, int microfragmentsQuantity, std::string photograph)
{
    this->id = id;
    this->size = size;
    this->infectionLevel = infectionLevel;
    this->microfragmentsQuantity = microfragmentsQuantity;
    this->photograph = photograph;
}

Material::Material(const Material &source)
{
    this->id = source.id;
    this->size = source.size;
    this->infectionLevel = source.infectionLevel;
    this->microfragmentsQuantity = source.microfragmentsQuantity;
    this->photograph = source.photograph;
}

Material::~Material()
{
}

Material& Material::operator=(Material const& source)
{
    this->id = source.id;
    this->size = source.size;
    this->infectionLevel = source.infectionLevel;
    this->microfragmentsQuantity = source.microfragmentsQuantity;
    this->photograph = source.photograph;

    return *this;
}

std::string Material::Id() const
{
    return this->id;
}

std::string Material::Size() const
{
    return this->size;
}

float Material::InfectionLevel() const
{
    return infectionLevel;
}

int Material::MicrofragmentsQuantity() const
{
    return microfragmentsQuantity;
}

std::string Material::Photograph() const
{
    return photograph;
}

std::ostream & operator<<(std::ostream & outStream, Material const& material)
{
    outStream << material.Id() << ", " << material.Size() << ", " << material.InfectionLevel() << ", " << material.MicrofragmentsQuantity() << ", " << material.Photograph();
    return outStream;
}

std::istream & operator>>(std::istream& inStream, Material& material)
{
    string itemString = "";

    string id = "";
    string size = "";
    float infectionLevel = 0;
    int microfragmentsQuantity = 0;
    string photograph = "";

    getline(inStream, itemString);

    if (itemString != "")
    {
        int substringPosition = itemString.find(", ");
        id = itemString.substr(0, substringPosition);

        itemString = itemString.substr(substringPosition + 2);
        substringPosition = itemString.find(", ");
        size = itemString.substr(0, substringPosition);

        itemString = itemString.substr(substringPosition + 2);
        substringPosition = itemString.find(", ");
        infectionLevel = stof(itemString.substr(0, substringPosition));

        itemString = itemString.substr(substringPosition + 2);
        substringPosition = itemString.find(", ");
        microfragmentsQuantity = stoi(itemString.substr(0, substringPosition));

        photograph = itemString.substr(substringPosition + 2);
    }

    material.id = id;
    material.size = size;
    material.infectionLevel = infectionLevel;
    material.microfragmentsQuantity = microfragmentsQuantity;
    material.photograph = photograph;

    return inStream;

}
