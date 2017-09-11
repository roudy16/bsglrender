#include "Program.h"

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "ShaderLoader.h"

using namespace std;
using namespace glm;

namespace bsgl {

Program::Program(const vector<GLuint>& shader_handles) {
    hndl = glCreateProgram();
    for (auto shader_handle : shader_handles) {
        glAttachShader(hndl, shader_handle);
    }

    glLinkProgram(hndl);
    checkLinkSuccess(hndl);
}

GLint Program::getUniform(const std::string& name) {
    GLint uniform_loc = -1;
    auto&& it = uniforms.find(name);
    if (it == uniforms.end()) {
        uniform_loc = glGetUniformLocation(hndl, name.c_str());
        uniforms[name] = uniform_loc;
    } else {
        uniform_loc = it->second;
    }
    return uniform_loc;
}

GLint Program::getAttribute(const std::string& name) {
    GLint attr_loc = -1;
    auto&& it = attributes.find(name);
    if (it == attributes.end()) {
        attr_loc = glGetAttribLocation(hndl, name.c_str());
        attributes[name] = attr_loc;
    } else {
        attr_loc = it->second;
    }
    return attr_loc;
}

}