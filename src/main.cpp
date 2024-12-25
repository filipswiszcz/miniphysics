#include <iostream>

#include <rush/entity/camera.hpp>
extern "C" {
    #include <rush/util/log.h>
}
#include <rush/util/resource_loader.hpp>
#include <rush/util/shader_loader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const size_t WIDTH = 1280;
const size_t HEIGHT = 960;
const char* WINDOW_NAME = "rush (BUILD v0.1.5)";

bool is_first_play = true;

void mouse_input(GLFWwindow *window, entity::Camera &camera) {
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);

    if (is_first_play) {
        camera.set_mouse_x(mouse_x);
        camera.set_mouse_y(mouse_y);

        is_first_play = false;
    }

    float offset_x = mouse_x - camera.get_mouse_x();
    float offset_y = camera.get_mouse_y() - mouse_y;

    camera.set_mouse_x(mouse_x);
    camera.set_mouse_y(mouse_y);

    offset_x *= camera.get_sensitivity();
    offset_y *= camera.get_sensitivity();

    camera.set_yaw(camera.get_yaw() + offset_x);
    camera.set_pitch(camera.get_pitch() + offset_y);

    if (camera.get_pitch() > 89.0f) camera.set_pitch(89.0f);
    if (camera.get_pitch() < -89.0f) camera.set_pitch(-89.0f);

    glm::vec3 t;
    t.x = glm::cos(glm::radians(camera.get_yaw())) * glm::cos(glm::radians(camera.get_pitch()));
    t.y = glm::sin(glm::radians(camera.get_pitch()));
    t.z = glm::sin(glm::radians(camera.get_yaw())) * glm::cos(glm::radians(camera.get_pitch()));

    camera.set_target_position(glm::normalize(t));
}

void keyboard_input(GLFWwindow *window, entity::Camera &camera) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.set_position(camera.get_position() + (camera.get_target_position() * camera.get_speed()));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.set_position(camera.get_position() - (camera.get_target_position() * camera.get_speed()));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.set_position(camera.get_position() - glm::normalize(glm::cross(camera.get_target_position(), camera.get_up_position())) * camera.get_speed());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.set_position(camera.get_position() + glm::normalize(glm::cross(camera.get_target_position(), camera.get_up_position())) * camera.get_speed());
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {

    GLFWwindow *window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
    if (!window) {
        log_fatal("failed to create window"); glfwTerminate(); return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    // shader code
    std::string vertex_shader_code = util::read_shader_file("shaders/basic.vs");
    std::string frag_shader_code = util::read_shader_file("shaders/basic.fs");
    GLuint vertex_shader = util::compile_shader(vertex_shader_code, GL_VERTEX_SHADER);
    GLuint frag_shader = util::compile_shader(frag_shader_code, GL_FRAGMENT_SHADER);

    GLuint program = util::link_shaders(vertex_shader, frag_shader);
    // end of shader code

    // render with depth
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // texture
    unsigned int temp_texture = util::temp_load_texture("resources/textures/witcher_wallpaper.jpg");

    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "temp_texture"), 0);
    // end of texture

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, &projection[0][0]);

    entity::Camera camera;
    camera.set_position(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.set_target_position(glm::vec3(0.0f, 0.0f, -1.0f));
    camera.set_up_position(glm::vec3(0.0f, 1.0f, 0.0f));

    while (!glfwWindowShouldClose(window)) {
        // inputs
        keyboard_input(window, camera);
        mouse_input(window, camera);

        // render commands
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, temp_texture);

        glUseProgram(program);

        glm::mat4 view = camera.get_look_at();
        glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, &view[0][0]);

        glBindVertexArray(vao);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &model[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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