#pragma once
#include <glad/glad.h>



struct Texture {
    GLuint id;

    static Texture fromFile(char fisier[]);
};
