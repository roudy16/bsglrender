#pragma once

#include <string>
#include <GL/glew.h>
#include "Constants.h"
#include "ShaderLoader.h"

namespace bsgl {

template <ShaderType T>
class Shader {
public:
    Shader() = default;
    Shader(const std::string& filename);

    ~Shader() {
        if (is_loaded) {
            glDeleteShader(hndl);
        }
    }

    GLuint getHandle() const {
        return hndl;
    }

private:
    GLuint hndl = ~0;
    bool is_loaded = false;
};

template <ShaderType T>
Shader<T>::Shader(const std::string&) {
    static_assert(false, "Specialization needed for this shader type");
}

template <>
inline Shader<ShaderType::vertex>::Shader(const std::string& filename) {
    hndl = bsgl::loadVertexShader(filename);
    is_loaded = true;
}

template <>
inline Shader<ShaderType::fragment>::Shader(const std::string& filename) {
    hndl = bsgl::loadFragmentShader(filename);
    is_loaded = true;
}

template <>
inline Shader<ShaderType::geometry>::Shader(const std::string& filename) {
    hndl = bsgl::loadGeometryShader(filename);
    is_loaded = true;
}

}