#include "MeshRenderer.h"

using namespace std;

namespace bsgl {

void MeshRenderer::setVertexData(const vector<vertex_t>& in_data) {
    vertex_data = in_data;
}

void MeshRenderer::setMaterial(Material* in_mat) {
    mat = in_mat;
}

void MeshRenderer::prepare(GLuint* vbos) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static vertex_t vertices[TRI_VALS] = {
             0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f };
    static GLushort indices[NUM_VERTICES] = { 0, 1, 2 };

    glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEXATTR_BUFFER_IDX]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX_BUFFER_IDX]);
    glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * (VERT_POS_SIZE + VERT_COLOR_SIZE) * sizeof(vertex_t), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_VERTICES * sizeof(GLushort), indices, GL_STATIC_DRAW);

    size_t offset = 0;
    GLint posAttrib = mat->getProgram()->getAttribute("position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, VERT_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);
    offset += VERT_POS_SIZE * sizeof(vertex_t);
    GLint colAttrib = mat->getProgram()->getAttribute("color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, VERT_COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);

}

void MeshRenderer::draw(glm::mat4 view_proj) {
    mat->getProgram()->use();

    glm::mat4 model(1.0f);
    glm::mat4 mvp = view_proj * model;
    mat->getProgram()->setUniform("mvp", mvp);

    glDrawElements(GL_TRIANGLES, NUM_VERTICES, GL_UNSIGNED_SHORT, nullptr);
}

}