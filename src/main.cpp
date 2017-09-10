#include <exception>
#include <iostream>
#include <cmath>
#include <cstdio>

#include <GL/glew.h>
#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"

#include "ShaderLoader.h"
#include "Camera.h"
#include "Constants.h"
#include "utils.h"

using namespace std;

#define  LOG(...)   printf(__VA_ARGS__);printf("\n");


GLFWwindow* createWindow(uint32_t width, uint32_t height) {
    // Create an application window with the following settings:
    GLFWwindow* window = glfwCreateWindow(
        width,                            // width, in pixels
        height,                           // height, in pixels
        "A GLFW window",                  // window title
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        throw runtime_error("Failed to create Window");
    }

    return window;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void setOpenGLAttributes() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

void init() {
    cout << "Okay Now" << endl;
    if (!glfwInit()) {
        throw runtime_error("Failed to init GLFW");
    }
    glfwSetErrorCallback(error_callback);
}

void initVertexBufferObjects(vertex_t* vertex_buffer, GLushort* indices, GLuint num_vertices, GLuint num_indices, GLuint* vbod_ids) {
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(NUM_VBOS, vbod_ids);
    glBindBuffer(GL_ARRAY_BUFFER, vbod_ids[VERTEXATTR_BUFFER_IDX]);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * (VERT_POS_SIZE + VERT_COLOR_SIZE) * sizeof(vertex_t), vertex_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbod_ids[INDEX_BUFFER_IDX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

int main(int argc, char* argv[]) {
    try {
        init();
        setOpenGLAttributes();
        GLFWwindow* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            fprintf(stderr, "Error: %s", glewGetErrorString(err));
            throw runtime_error("Failed to init GLEW");
        }

        glClearColor(0, 0, 0, 1);
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Create Vertex Array Object
        //GLuint vao;
        //glGenVertexArraysOES(1, &vao);
        //glBindVertexArrayOES(vao);

        GLuint vbos[NUM_VBOS];

        static vertex_t vertices[TRI_VALS] = {
                 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f };
        static GLushort indices[NUM_VERTICES] = { 0, 1, 2 };
        initVertexBufferObjects(vertices, indices, NUM_VERTICES, NUM_VERTICES, vbos);

        OP::LoadDefaultShaderProgs();
        GLuint basic_min_hndl = OP::GetShaderProgHandle("basic_min");
        glUseProgram(basic_min_hndl);

        size_t offset = 0;
        GLint posAttrib = glGetAttribLocation(basic_min_hndl, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, VERT_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);
        offset += VERT_POS_SIZE * sizeof(vertex_t);
        GLint colAttrib = glGetAttribLocation(basic_min_hndl, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, VERT_COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);
        GLint mvpUniformLoc = glGetUniformLocation(basic_min_hndl, "mvp");

        Camera cam;

        while (!glfwWindowShouldClose(window)) {
            // Clear the screen to black
            //glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEXATTR_BUFFER_IDX]);
            glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * (VERT_POS_SIZE + VERT_COLOR_SIZE) * sizeof(vertex_t), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[INDEX_BUFFER_IDX]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_VERTICES * sizeof(GLushort), indices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(posAttrib);
            glEnableVertexAttribArray(colAttrib);
            offset = 0;
            glVertexAttribPointer(posAttrib, VERT_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);
            offset += VERT_POS_SIZE * sizeof(vertex_t);
            glVertexAttribPointer(colAttrib, VERT_COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)offset);

            glm::mat4 model(1.0f);
            cam.RotateRoll(0.05f);
            glm::mat4 mvp = cam.Projection() * cam.View() * model;
            glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, &mvp[0][0]);

            // Draw a triangle from the 3 vertices
            glDrawElements(GL_TRIANGLES, NUM_VERTICES, GL_UNSIGNED_SHORT, nullptr);

            glDisableVertexAttribArray(posAttrib);
            glDisableVertexAttribArray(colAttrib);

            glfwPollEvents();

            glfwSwapBuffers(window);
        }

        // Clean up
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    catch (exception e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}