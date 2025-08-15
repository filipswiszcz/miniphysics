#include "game.h"

// public

void Game::initialize() {
    QSSERT(glfwInit(), "Failed to initialize GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this -> window = {800, 600, "Wow!"};
    
    this -> context = {};
    this -> context.window = glfwCreateWindow(this -> window.width, this -> window.height, this -> window.name.c_str(), NULL, NULL);
    QSSERT(this -> context.window, "Failed to create OpenGL window\n");

    glfwMakeContextCurrent(this -> context.window);
    glfwSetInputMode(this -> context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#ifndef __APPLE__
    glewExperimental = 1;
    QSSERT(glewInit(), "Failed to initialize GLEW\n");
#endif

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // SHADERS
    this -> context.shader.create_program("shader/default.vs", "shader/default.fs");
    this -> crosshair.shader.create_program("shader/crosshair.vs", "shader/crosshair.fs");

    // CAMERA
    double mx, my;
    glfwGetCursorPos(this -> context.window, &mx, &my);
    this -> camera.mx = mx;
    this -> camera.my = my;
    this -> camera.position = Vec3(0.0f, 1.0f, 3.0f);
    this -> camera.target = Vec3(0.0f, 0.0f, -1.0f);
    this -> camera.head = Vec3(0.0f, 1.0f, 0.0f);
    this -> camera.yaw = -90.0f;
    this -> camera.pitch = 0.0f;
    this -> camera.speed = 2.0f;
    this -> camera.sensitivity = 0.2f;

    // CROSSHAIR
    this -> initialize_crosshair();

    // TEST
    // del s
    this -> context.mesh = mesh_read("assets/default/plane.obj");
    // mesh_upload(&this -> context.mesh);

    this -> context.fabric.initialize(&this -> context.mesh);

    this -> time_between_frames = 0.16f; // del
    // del e
}

void Game::update() {
    while (!glfwWindowShouldClose(this -> context.window)) {
        // INPUTS
        this -> handle_mouse();
        this -> handle_keyboard();

        // FPS
        this -> record_frames();
        
        // BACKGROUND
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // CROSSHAIR
        glUseProgram(this -> crosshair.shader.get_program());
        this -> draw_crosshair();

        // del s
        glUseProgram(this -> context.shader.get_program());

        Mat4_t projection = perspective(radians(45.0f), (float) this -> window.width / (float) this -> window.height, 0.1f, 100.0f);
        this -> context.shader.set_mat4("projection", projection);
        Mat4_t view = look_at(this -> camera.position, (this -> camera.position + this -> camera.target), this -> camera.head);
        this -> context.shader.set_mat4("view", view);
        Mat4_t model = Mat4(1.0f);
        model = translate(model, Vec3(0.0f, 0.0f, 1.0f));
        this -> context.shader.set_mat4("model", model);

        // mesh_draw(&this -> context.mesh);
        this -> context.fabric.draw();

        double mx, my; // mouse x/y
        glfwGetCursorPos(this -> context.window, &mx, &my);
        this -> context.fabric.destroy(mx, my);
        // del e

        glfwSwapBuffers(this -> context.window);
        glfwPollEvents();
    }
}

void Game::stop() {
    // clear buffers
    glfwTerminate();
}

// private

void Game::record_frames() {
   float ctm = (float) glfwGetTime();
   this -> time_between_frames = ctm - this -> time_of_last_frame;
   this -> time_of_last_frame = ctm;
   this -> frames_per_second++;
   if (this -> time_between_frames >= 1.0f) {
        this -> frames_per_second = 0;
        this -> time_of_last_frame = 1.0f;
   }
}

void Game::handle_mouse() {
    double mx, my; // mouse x/y
    glfwGetCursorPos(this -> context.window, &mx, &my);

    float ox = mx - this -> camera.mx; // offset x/y
    float oy = this -> camera.my - my;

    this -> camera.mx = mx;
    this -> camera.my = my;

    ox *= this -> camera.sensitivity;
    oy *= this -> camera.sensitivity;

    this -> camera.yaw = (this -> camera.yaw + ox);
    this -> camera.pitch = (this -> camera.pitch + oy);

    if (this -> camera.pitch > 89.0f) this -> camera.pitch = 89.0f;
    if (this -> camera.pitch < -89.0f) this -> camera.pitch = -89.0f;

    Vec3_t target = Vec3(cos(radians(this -> camera.yaw)) * cos(radians(this -> camera.pitch)), sin(radians(this -> camera.pitch)), sin(radians(this -> camera.yaw)) * cos(radians(this -> camera.pitch)));

    this -> camera.target = normalize(target);
}

void Game::handle_keyboard() {
    if (glfwGetMouseButton(this -> context.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        this -> context.fabric.set_rmb(1);
    }
    if (glfwGetMouseButton(this -> context.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        this -> context.fabric.set_rmb(0);
    if (glfwGetKey(this -> context.window, GLFW_KEY_W) == GLFW_PRESS)
        this -> camera.position = this -> camera.position + (this -> camera.target * (this -> camera.speed * this -> time_between_frames));
    if (glfwGetKey(this -> context.window, GLFW_KEY_S) == GLFW_PRESS)
        this -> camera.position = this -> camera.position - (this -> camera.target * (this -> camera.speed * this -> time_between_frames));
    if (glfwGetKey(this -> context.window, GLFW_KEY_A) == GLFW_PRESS)
        this -> camera.position = this -> camera.position - (normalize(cross(this -> camera.target, this -> camera.head)) * (this -> camera.speed * this -> time_between_frames));
    if (glfwGetKey(this -> context.window, GLFW_KEY_D) == GLFW_PRESS)
        this -> camera.position = this -> camera.position + (normalize(cross(this -> camera.target, this -> camera.head)) * (this -> camera.speed * this -> time_between_frames));
    if (glfwGetKey(this -> context.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this -> camera.speed = 4.0f;
    if (glfwGetKey(this -> context.window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        this -> camera.speed = 2.0f;
    if (glfwGetKey(this -> context.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this -> context.window, 1);
}

void Game::initialize_crosshair() {
    glGenVertexArrays(1, &this -> crosshair.vao);
    glGenBuffers(1, &this -> crosshair.vbo);

    glBindVertexArray(this -> crosshair.vao);

    glBindBuffer(GL_ARRAY_BUFFER, this -> crosshair.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2_t), &this -> crosshair.position, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2_t), (void*) 0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Game::draw_crosshair() {
    glBindVertexArray(this -> crosshair.vao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}