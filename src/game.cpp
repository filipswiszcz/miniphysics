#include "game.h"

void Game::initialize() {
    ASSERT(glfwInit(), "Failed to initialize GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this -> window = {800, 600, "Wow!"};
    
    this -> context = {};
    this -> context.window = glfwCreateWindow(this -> window.width, this -> window.height, this -> window.name.c_str(), NULL, NULL);
    ASSERT(this -> context.window, "Failed to create OpenGL window\n");

    glfwMakeContextCurrent(this -> context.window);

#ifndef __APPLE__
    glewExperimental = 1;
    ASSERT(glewInit(), "Failed to initialize GLEW\n");
#endif

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
