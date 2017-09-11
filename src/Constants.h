#pragma once

#include <GL/glew.h>

namespace bsgl {

using vertex_t = GLfloat;

constexpr size_t NUM_VBOS = 2;
constexpr size_t VERTEXATTR_BUFFER_IDX = 0;
constexpr size_t INDEX_BUFFER_IDX = 1;
constexpr GLuint NUM_VERTICES = 3;
constexpr GLuint VERT_POS_SIZE = 3; // x, y, z
constexpr GLuint VERT_COLOR_SIZE = 4; // r, g, b, a
constexpr GLuint TRI_VALS = NUM_VERTICES * (VERT_POS_SIZE + VERT_COLOR_SIZE);
constexpr size_t VERTEX_STRIDE = sizeof(vertex_t) * (VERT_POS_SIZE + VERT_COLOR_SIZE);

constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 640;
constexpr GLfloat NEAR_CLIP = 0.1f;
constexpr GLfloat FAR_CLIP = 100.0f;
constexpr GLfloat DEFAULT_FOV = 60.0f;

enum class ShaderType : uint16_t {
    vertex, fragment, geometry
};
}
