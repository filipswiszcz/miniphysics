#include "game.h"

void Game::initialize() {
    if (!glfwInit()) {return;}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this -> window = {800, 600, "Wow!"};
    
    this -> context = {};
    this -> context.window = glfwCreateWindow(this -> window.width, this -> window.height, this -> window.name.c_str(), NULL, NULL);
    if (!this -> context.window) {return;}

    glfwMakeContextCurrent(this -> context.window);
}

void Game::loop() {
    while (!glfwWindowShouldClose(this -> context.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(this -> context.window);
        glfwPollEvents();
    }
}

void Game::stop() {
    // clear buffers
    glfwTerminate();
}
