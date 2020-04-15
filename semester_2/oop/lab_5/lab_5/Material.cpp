#include "Material.h"


Material::Material()
{
    this->id = "";
    this->size = "0X0X0";
    this->infectionLevel = 0.0;
    this->microfragmentsQuantity = 0;
    this->photograph = "";
}

Material::Material(std::string id, std::string size, float infectionLevel, int microfragmentsQuantity, std::string photograph)
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
