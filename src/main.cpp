#include <exception>
#include <iostream>
#include <cmath>
#include <cstdio>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "ShaderLoader.h"
#include "Camera.h"
#include "Constants.h"
#include "utils.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Program.h"

using namespace std;
using namespace bsgl;

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

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void setOpenGLAttributes() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void init() {
    cout << "Okay Now" << endl;
    if (!glfwInit()) {
        throw runtime_error("Failed to init GLFW");
    }
    glfwSetErrorCallback(error_callback);
}

void initVertexBufferObjects(GLuint* vbod_ids) {
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(NUM_VBOS, vbod_ids);
    glBindBuffer(GL_ARRAY_BUFFER, vbod_ids[VERTEXATTR_BUFFER_IDX]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbod_ids[INDEX_BUFFER_IDX]);
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

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        loadDefaultShaderProgs();

        GLuint vbos[NUM_VBOS];
        initVertexBufferObjects(vbos);

        Material basic_mat(getShaderProgram("basic_min"));
        MeshRenderer tri;
        tri.setMaterial(&basic_mat);
        tri.prepare(vbos);

        Camera cam;

        while (!glfwWindowShouldClose(window)) {
            // Clear the screen to black
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            cam.RotateRoll(0.05f);
            glm::mat4 vp = cam.Projection() * cam.View();
            tri.draw(vp);

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