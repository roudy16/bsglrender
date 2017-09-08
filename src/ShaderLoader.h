#pragma once
#include <string>

#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"

namespace OP {
    GLuint LoadVertexShader(const std::string& filepath);
    GLuint LoadFragmentShader(const std::string& filepath);
    GLuint GetShaderProgHandle(const std::string& name);
    void LoadDefaultShaderProgs();
}

