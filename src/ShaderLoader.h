#pragma once
#include <string>

#include "GLFW/glfw3.h"

namespace bsgl {

GLuint LoadVertexShader(const std::string& filepath);
GLuint LoadFragmentShader(const std::string& filepath);
GLuint GetShaderProgHandle(const std::string& name);
void LoadDefaultShaderProgs();

}

