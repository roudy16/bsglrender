#pragma once
#include <string>

#include "GLFW/glfw3.h"

namespace bsgl {

class Program;

GLuint loadVertexShader(const std::string& filepath);
GLuint loadFragmentShader(const std::string& filepath);
GLuint loadGeometryShader(const std::string& filepath);
Program* getShaderProgram(const std::string& name);
void loadDefaultShaderProgs();
bool checkCompileSuccess(GLuint hndl);
bool checkLinkSuccess(GLuint hndl);

}

