#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace bsgl {

class Program {
public:
    Program() = default;
    Program(const std::vector<GLuint>& shader_handles);

    GLuint getHandle() const { return hndl; }
    GLint getUniform(const std::string& name);
    GLint getAttribute(const std::string& name);

    template <typename T>
    void setUniform(const std::string& name, const T& val);

    void use() {
        glUseProgram(hndl);
    }

private:
    std::unordered_map<std::string, GLint> uniforms;
    std::unordered_map<std::string, GLint> attributes;

    GLuint hndl = ~0;
};

template <typename T>
void Program::setUniform(const std::string& , const T& ) {
    static_assert(false, "Need to provide specialization for this type");
}

template <>
inline void Program::setUniform(const std::string& name, const glm::mat4& val) {
    GLint uniform_handle = getUniform(name);
    glUniformMatrix4fv(uniform_handle, 1, GL_FALSE, &val[0][0]);
}

template <>
inline void Program::setUniform(const std::string& name, const glm::vec4& val) {
    GLint uniform_handle = getUniform(name);
    glUniform4fv(uniform_handle, 1, &val[0]);
}

template <>
inline void Program::setUniform(const std::string& name, const glm::vec3& val) {
    GLint uniform_handle = getUniform(name);
    glUniform3fv(uniform_handle, 1, &val[0]);
}

template <>
inline void Program::setUniform(const std::string& name, const glm::vec2& val) {
    GLint uniform_handle = getUniform(name);
    glUniform2fv(uniform_handle, 1, &val[0]);
}

template <>
inline void Program::setUniform(const std::string& name, const GLfloat& val) {
    GLint uniform_handle = getUniform(name);
    glUniform1f(uniform_handle, val);
}


}
