#include <exception>
#include <iostream>
#include <cmath>
#include <cstdio>

#include <GL/glew.h>
#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"

#include "ShaderLoader.h"
#include "utils.h"

using namespace std;

#define  LOG(...)   printf(__VA_ARGS__);printf("\n");


constexpr uint32_t window_width = 800;
constexpr uint32_t window_height = 640;

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

int main(int argc, char* argv[]) {
    try {
        init();
        setOpenGLAttributes();
        GLFWwindow* window = createWindow(window_width, window_height);
        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            fprintf(stderr, "Error: %s", glewGetErrorString(err));
            throw runtime_error("Failed to init GLEW");
        }

        glClearColor(0, 0, 0, 1);
        glViewport(0, 0, window_width, window_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Create Vertex Array Object
        //GLuint vao;
        //glGenVertexArraysOES(1, &vao);
        //glBindVertexArrayOES(vao);

        // Create a Vertex Buffer Object and copy the vertex data to it
        GLuint vbo;
        glGenBuffers(1, &vbo);

        GLfloat vertices[] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        OP::LoadDefaultShaderProgs();
        GLuint basic_min_hndl = OP::GetShaderProgHandle("basic_min");
        glUseProgram(basic_min_hndl);

        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(basic_min_hndl, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5, 0);

        GLint colAttrib = glGetAttribLocation(basic_min_hndl, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5, (void*)(sizeof(float) * 2));

        while (!glfwWindowShouldClose(window)) {
            // Clear the screen to black
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(basic_min_hndl);
            // Draw a triangle from the 3 vertices
            glDrawArrays(GL_TRIANGLES, 0, 3);

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