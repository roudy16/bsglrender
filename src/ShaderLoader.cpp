#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include "Program.h"
#include "Shader.h"
#include "ShaderLoader.h"

using namespace std;

namespace bsgl {

using shader_map_key_t = string;
using vert_shader_map_val_t = Shader<ShaderType::vertex>;
using frag_shader_map_val_t = Shader<ShaderType::fragment>;
using geom_shader_map_val_t = Shader<ShaderType::geometry>;
using shader_prog_map_val_t = Program;
using vert_shader_map_t = unordered_map<shader_map_key_t, vert_shader_map_val_t>;
using frag_shader_map_t = unordered_map<shader_map_key_t, frag_shader_map_val_t>;
using geom_shader_map_t = unordered_map<shader_map_key_t, geom_shader_map_val_t>;
using shader_prog_map_t = unordered_map<shader_map_key_t, shader_prog_map_val_t>;

class ShaderManager {
public:
    vert_shader_map_t vert_shaders;
    frag_shader_map_t frag_shaders;
    geom_shader_map_t geom_shaders;
    shader_prog_map_t shader_progs;
};

static ShaderManager g_shader_mgr;

void loadDefaultShaderProgs() {
    Shader<ShaderType::vertex> basic_vert(".\\shaders\\basic_min.vert");
    Shader<ShaderType::fragment> basic_frag(".\\shaders\\basic_min.frag");

    Program prog({ basic_vert.getHandle(), basic_frag.getHandle() });

    g_shader_mgr.vert_shaders["basic_min"] = basic_vert;
    g_shader_mgr.frag_shaders["basic_min"] = basic_frag;
    g_shader_mgr.shader_progs["basic_min"] = prog;
}

GLuint loadShader(const string& filename, GLenum type);

GLuint loadFragmentShader(const string& filepath) {
    GLuint hndl = loadShader(filepath, GL_FRAGMENT_SHADER);
    return hndl;
}

GLuint loadVertexShader(const string& filepath) {
    GLuint hndl = loadShader(filepath, GL_VERTEX_SHADER);
    return hndl;
}

GLuint loadGeometryShader(const string& filepath) {
    GLuint hndl = loadShader(filepath, GL_GEOMETRY_SHADER);
    return hndl;
}

Program* getShaderProgram(const string& name) {
    auto&& prog_map = g_shader_mgr.shader_progs;
    auto iter = prog_map.find(name);
    if (iter == prog_map.end()) {
        return nullptr;
    }
    return &iter->second;
}

GLuint loadShader(const string& filename, GLenum type) {
    char* source = nullptr;
    ifstream file(filename, ifstream::in | ifstream::binary | ifstream::ate);
    size_t size;

    if (file.is_open()) {
        streampos sz = file.tellg();
        size = static_cast<size_t>(sz);
        source = new char[size + 1];
        file.seekg(0, ios::beg);
        file.read(source, sz);
        file.close();
        source[size] = '\0';
    }
    else {
        cerr << "Failed to load " + filename << endl;
        return -1;
    }

    GLuint shdr_hndl = glCreateShader(type);
    glShaderSource(shdr_hndl, 1, &source, NULL);
    glCompileShader(shdr_hndl);
    if (!checkCompileSuccess(shdr_hndl)) {
        glDeleteShader(shdr_hndl); // Don't leak the shader.
        shdr_hndl = -1;
    }

    delete[] source;
    return shdr_hndl;
}

static bool checkShaderSuccess(GLuint hndl, GLuint type) {
}

bool checkCompileSuccess(GLuint hndl) {
    GLint success = GL_FALSE;
    glGetShaderiv(hndl, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(hndl, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(hndl, maxLength, &maxLength, &errorLog[0]);
        cerr << &errorLog[0] << endl;
    }
    return success != GL_FALSE;
}

bool checkLinkSuccess(GLuint hndl) {
    GLint success = GL_FALSE;
    glGetProgramiv(hndl, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(hndl, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(hndl, maxLength, &maxLength, &errorLog[0]);
        cerr << &errorLog[0] << endl;
    }
    return success != GL_FALSE;
}

}
