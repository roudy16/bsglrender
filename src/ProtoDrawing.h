#pragma once

#include "glm/vec3.hpp"

namespace bsgl {

class LineSeg {
    glm::vec3 m_pos0;
    glm::vec3 m_pos1;

    void draw();
};

}