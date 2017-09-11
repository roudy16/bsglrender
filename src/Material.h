#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "Program.h"

namespace bsgl {

class Material {
public:
    Material() = default;
    Material(Program* prog) : program(prog) {}

    void prepare();
    Program* getProgram() { return program; }

private:
    Program* program;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

}
