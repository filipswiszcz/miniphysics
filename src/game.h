#ifndef __GAME_H__
#define __GAME_H__

#include <string>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#else
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

#include "common.h"
#include "shader.h"

typedef struct Window {
    int width, height;
    std::string name;
} Window_t;

typedef struct Context {
    GLFWwindow *window;
} Context_t;

class Game {
public:
    void initialize();
    void loop();
    void stop();
private:
    Window_t window;
    Context_t context;
};

#endif // !__GAME_H__
