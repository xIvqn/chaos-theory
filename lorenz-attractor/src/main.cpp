#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"

void configScene();

void renderScene();

void drawObjects(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V);

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void funFramebufferSize(GLFWwindow *window, int width, int height);

void funKey (GLFWwindow* window, int key, int scancode, int action, int mods);

void funScroll(GLFWwindow *window, double xoffset, double yoffset);

void funCursorPos(GLFWwindow *window, double xpos, double ypos);

struct Position {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

// Shaders
Shaders shaders;

// Models
Model sphere;

// Viewport
int w = 1000;
int h = 1000;

Position pos = {0.1, 0, 0};
float sigma = 10, rho = 28, beta = 8.0 / 3.0;

std::vector<glm::mat4> vector;

// Camera movement
float fovy = 60.0;
float alphaX = 0.0;
float alphaY = 0.0;

int main() {

    // Initialize GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    GLFWwindow *window;
    window = glfwCreateWindow(w, h, "Lorenz Attractor Visualizer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;

    // Configure callbacks
    glfwSetFramebufferSizeCallback(window, funFramebufferSize);
    glfwSetKeyCallback(window, funKey);
    glfwSetScrollCallback(window, funScroll);
    glfwSetCursorPosCallback(window, funCursorPos);

    // Rendering loop
    configScene();
    while (!glfwWindowShouldClose(window)) {
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void configScene() {

    // Depth test
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);

    // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl", "resources/shaders/fshader.glsl");

    // Models
    sphere.initModel("resources/models/sphere.obj");

}

void renderScene() {

    // Remove color buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Indicate shaders usage
    shaders.useShaders();

    // P matrix
    float nplane = 0.1;
    float fplane = 250.0;
    float aspect = (float) w / (float) h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // V matrix
    float x = 150.0f * glm::cos(glm::radians(alphaY)) * glm::sin(glm::radians(alphaX));
    float y = 150.0f * glm::sin(glm::radians(alphaY));
    float z = 150.0f * glm::cos(glm::radians(alphaY)) * glm::cos(glm::radians(alphaX));
    glm::vec3 eye(x, y, z);
    glm::vec3 center(0.0, 0.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);
    glm::mat4 V = glm::lookAt(eye, center, up);
    shaders.setVec3("ueye", eye);

    // New point calculation
    float dt = 0.01;
    float dx = (sigma * (pos.y - pos.x)) * dt;
    float dy = (pos.x * (rho - pos.z) - pos.y) * dt;
    float dz = (pos.x * pos.y - beta * pos.z) * dt;
    pos.x += dx;
    pos.y += dy;
    pos.z += dz;

    // M matrix
    float scale = 0.1;
    glm::mat4 S = glm::scale(I, glm::vec3(scale, scale, scale));
    glm::mat4 T = glm::translate(I, glm::vec3(pos.x, pos.y, pos.z));
    glm::mat4 CubeM = T * S;

    vector.push_back(CubeM);

    // Draw shape
    drawObjects(sphere, glm::vec3(1.0, 0.0, 0.0), P, V);

}

void drawObjects(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V) {

    for (int i = 0; i < vector.size(); ++i) {
        drawObject(model, color, P, V, vector.at(i));
    }

}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uPVM", P * V * M);

    glEnable(GL_POLYGON_OFFSET_FILL);
    shaders.setVec3("uColor", color);
    model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);

    shaders.setVec3("uColor", glm::vec3(1.0, 1.0, 1.0));
    model.renderModel(GL_LINE);

}

void funFramebufferSize(GLFWwindow *window, int width, int height) {

    // Viewport configuration
    glViewport(0, 0, width, height);

    // w and h update
    w = width;
    h = height;

}

void funKey (GLFWwindow* window, int key, int scancode, int action, int mods) {

    bool flag = true;
    
    if (action == GLFW_RELEASE) return;

    switch (key) {
        case GLFW_KEY_S: (mods == GLFW_MOD_SHIFT) ? sigma += 0.05 : sigma -= 0.05; break;
        case GLFW_KEY_R: (mods == GLFW_MOD_SHIFT) ? rho += 0.1 : rho -= 0.1; break;
        case GLFW_KEY_B: (mods == GLFW_MOD_SHIFT) ? beta += 0.025 : beta -= 0.025; break;
        default: flag = false;
    }

    if (flag) {
        if (sigma <= 0.0) sigma = 0.01;
        if (rho <= 0.0) rho = 0.01;
        if (beta <= 0.0) beta = 0.01;

        printf("Sigma: %f\t| Rho: %f\t| Beta: %f\n", sigma, rho, beta);
        fflush(stdout);

        vector.clear();

    }

}

void funScroll(GLFWwindow *window, double xoffset, double yoffset) {

    if (yoffset > 0) fovy -= fovy > 10.0f ? 5.0f : 0.0f;
    if (yoffset < 0) fovy += fovy < 90.0f ? 5.0f : 0.0f;

}

void funCursorPos(GLFWwindow *window, double xpos, double ypos) {

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) return;

    float limY = 89.0;
    alphaX = 90.0 * (2.0 * xpos / (float) w - 1.0);
    alphaY = 90.0 * (1.0 - 2.0 * ypos / (float) h);
    if (alphaY < -limY) alphaY = -limY;
    if (alphaY > limY) alphaY = limY;

}