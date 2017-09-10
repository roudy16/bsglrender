#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include "ShaderLoader.h"

using shader_map_key_t = std::string;
using shader_map_val_t = GLuint;
using shader_map_t = std::unordered_map<shader_map_key_t, shader_map_val_t>;

class ShaderManager {
public:
    shader_map_t vert_shaders;
    shader_map_t frag_shaders;
    shader_map_t shader_progs;
};

static ShaderManager g_shader_mgr;

void bsgl::LoadDefaultShaderProgs() {
    // Load and compile shaders
    GLuint basic_vert = bsgl::LoadVertexShader(".\\shaders\\basic_min.vert");
    GLuint basic_frag = bsgl::LoadFragmentShader(".\\shaders\\basic_min.frag");

    // Link Shader program. TODO make this its own function
    GLuint prog = glCreateProgram();
    glAttachShader(prog, basic_vert);
    glAttachShader(prog, basic_frag);
    glLinkProgram(prog);

    // Add the handles to the ShaderManager
    g_shader_mgr.vert_shaders["basic_min"] = basic_vert;
    g_shader_mgr.frag_shaders["basic_min"] = basic_frag;
    g_shader_mgr.shader_progs["basic_min"] = prog;
}

GLuint LoadShader(const std::string& filename, GLenum type) {
    char* source = nullptr;
    std::ifstream file(filename, std::ifstream::in|std::ifstream::binary|std::ifstream::ate);
    size_t size;

    if (file.is_open()) {
        std::streampos sz = file.tellg();
        size = static_cast<size_t>(sz);
        source = new char[size + 1];
        file.seekg(0, std::ios::beg);
        file.read(source, sz);
        file.close();
        source[size] = '\0';
    }
    else {
        std::cerr << "Failed to load " + filename << std::endl;
        return -1;
    }

    GLuint shdr_hndl = glCreateShader(type);
    glShaderSource(shdr_hndl, 1, &source, NULL);
    glCompileShader(shdr_hndl);
    GLint isCompiled = 0;
    glGetShaderiv(shdr_hndl, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shdr_hndl, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shdr_hndl, maxLength, &maxLength, &errorLog[0]);
        std::cerr << &errorLog[0] << std::endl;

        glDeleteShader(shdr_hndl); // Don't leak the shader.
    }

    delete[] source;

    return shdr_hndl;
}

GLuint bsgl::LoadFragmentShader(const std::string& filepath) {
    GLuint hndl = LoadShader(filepath, GL_FRAGMENT_SHADER);
    return hndl;
}

GLuint bsgl::LoadVertexShader(const std::string& filepath) {
    GLuint hndl = LoadShader(filepath, GL_VERTEX_SHADER);
    return hndl;
}

GLuint bsgl::GetShaderProgHandle(const std::string& name) {
    auto&& prog_map = g_shader_mgr.shader_progs;
    auto iter = prog_map.find(name);
    if (iter == prog_map.end()) {
        return 0;
    }
    return iter->second;
}
