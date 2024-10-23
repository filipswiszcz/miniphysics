#include <iostream>

#include <rush/util/shader_loader.hpp>

const size_t WIDTH = 1280;
const size_t HEIGHT = 960;
const char* WINDOW_NAME = "rush";

void input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void render() {}

int main() {
    GLFWwindow *window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
    if (!window) {
        std::cout << "err" << std::endl;
        glfwTerminate(); return -1;
    }

    glfwMakeContextCurrent(window);

    // shader code
    std::string vertex_shader_code = util::read_file("shaders/junk.glsl");
    std::string frag_shader_code = util::read_file("shaders/something.frag");
    GLuint vertex_shader = util::compile(vertex_shader_code, GL_VERTEX_SHADER);
    GLuint frag_shader = util::compile(frag_shader_code, GL_FRAGMENT_SHADER);

    GLuint program = util::link(vertex_shader, frag_shader);
    // end of shader code

    // render code
    float verticles[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.0f, 0.5f, 0.0f
        // 0.0f, -0.5f, 0.5f
    };

    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // end of render code

    while (!glfwWindowShouldClose(window)) {
        // inputs
        input(window);

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // idk something
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();

    return 0;
}