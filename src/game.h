#ifndef __GAME_H__
#define __GAME_H__

#include <iostream> // temporary
#include <chrono> // temporary

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
#include "mesh.h"
#include "shader.h"

typedef struct Window {
    int width, height;
    std::string name;
} Window_t;

typedef struct Context {
    GLFWwindow *window;
    // del s
    Shader shader;
    Fabric fabric;
    Mesh_t mesh;
    uint32_t vao, vbo, ibo;
    uint32_t indices[4];
    //del e
} Context_t;

typedef struct Camera {
    Vec3_t position;
    Vec3_t target, head;
    float mx, my; // mouse x/y
    float yaw, pitch;
    float speed, sensitivity;
} Camera_t;

typedef struct Crosshair {
    Vec2_t position;
    Shader shader;
    uint32_t vao, vbo;
} Crosshair_t;

class Game {
public:
    void initialize();
    void update();
    void stop();
private:
    Window_t window;
    // Context_t context;
    Camera_t camera;
    float time_between_frames;
    float time_of_last_frame;
    int frames_per_second;
    Crosshair_t crosshair;
    Context_t context;
    void record_frames();
    void handle_mouse();
    void handle_keyboard();
    void initialize_crosshair();
    void draw_crosshair();
};

// kernel (init, window, timing, mem management)

// scene manager (holds all current objects/entities, routes updates/renders to each)
  // menu, level, pause
  // characters, enemies, envinronment
  // update

// renderer (draws objects, backgrounds, UIs)
  // 

// input sys
  // mouse/keyboard and controller

// physics sys
  // movement, interactions, collisions

// audio sys
  // sound effects
  // music

// resource loader
  // loads models, textures, sounds


// boot: init subsystems (window, audio, renderer etc)
// main loop:
    // process input
    // update all game objects logic
        // ai/player decisions (moving, attacking etc)
        // animations
        // game events
    // physics calculations
    // render
    // audio
// scene swap (switch from menu to gameplay, load/unload assets)

#endif // !__GAME_H__
