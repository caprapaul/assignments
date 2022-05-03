#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"


struct Mesh {
public:
    // mesh data
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> uvs;

    static Mesh sphere(float radius, int sectorCount, int stackCount);
};

