#ifdef __APPLE__

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#endif

#include <iostream>

int main(int argc, char **argv) {
    if (!glfwInit()) return -1;
    std::cout << "hi" << std::endl;
    return 0;
}