#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include "Constants.h"

class Camera {
public:
    Camera()
        : projection(glm::perspective(glm::radians(DEFAULT_FOV), float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), NEAR_CLIP, FAR_CLIP)),
        view(), pos(0.0f, 0.0f, -10.0f), forward(0.0f, 0.0f, 1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f)
    {
        view = glm::lookAt(pos, pos + forward, up);
    }

    void Translate(glm::vec3 trans) {
        pos = pos + trans;
    }

    void RotateYaw(GLfloat rads) {
        Rotate(up, rads);
    }

    void RotatePitch(GLfloat rads) {
        Rotate(right, rads);
    }

    void RotateRoll(GLfloat rads) {
        Rotate(forward, rads);
    }

    void ChangeFOV(GLfloat deg) {
        projection = glm::perspective(glm::radians(deg), float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), NEAR_CLIP, FAR_CLIP);
    }

    glm::mat4 Projection() const {
        return projection;
    }

    glm::mat4 View() const {
        return view;
    }

private:

    void Rotate(glm::vec3 axis, GLfloat rads) {
        glm::mat4 rot(1.0f);
        rot = glm::rotate(rot, rads, axis);
        forward = glm::mat3(rot) * forward;
        up = glm::mat3(rot) * up;
        right = glm::mat3(rot) * right;
        view = glm::lookAt(pos, pos + forward, up);
    }

    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
};
