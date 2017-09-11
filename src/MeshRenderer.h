#pragma once
#include <vector>

#include <GL/glew.h>
#include "Constants.h"
#include "Material.h"


namespace bsgl {

class MeshRenderer {
public:
    MeshRenderer() = default;

    void setMaterial(Material* in_mat);
    void setVertexData(const std::vector<vertex_t>& in_data);
    void prepare(GLuint* vbos);
    void draw(glm::mat4 view_proj);

private:
    std::vector<vertex_t> vertex_data;
    Material* mat;
    GLuint vao;
};

}