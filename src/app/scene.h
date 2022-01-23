#ifndef FUOCO_APP_SCENE_H_
#define FUOCO_APP_SCENE_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../modules/shader.h"
#include "../modules/model.h"
#include "../modules/camera.h"
#include "../modules/textures.h"

bool isFirstMouseMovement = true;
float prevY = 0.0f;
float prevX = 0.0f;
float fov = 50.0f;

class Scene
{
public:
    glm::mat4 view;
    glm::mat4 proj;
    Camera camera;
    Shader modelShader;
    Model modelFromAssimp;

    Scene() : modelShader("./shaders/shader.vert", "./shaders/shader.frag"), modelFromAssimp("./assets/backpack/backpack.obj")
    {
        camera = Camera(glm::vec3(0, 0, 5), glm::vec3(0, 1, 0));
        // Shader lightShader("./shaders/light.vert", "./shaders/light.frag");
        modelShader.use();
        camera.Front = glm::vec3(0.0f, 0.0, -1.0f);
    }

    void update(float vWidth, float vHeight, float delta)
    {
        // model view proj
        proj = glm::perspective(glm::radians(fov), vWidth / vHeight, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        modelShader.use();
        modelShader.setMat4("model", model);
        modelShader.setMat4("view", view);
        modelShader.setMat4("proj", proj);

        modelFromAssimp.Draw(modelShader);
    }

    void processInput(GLFWwindow *window, float delta)
    {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(FORWARD, delta);
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(LEFT, delta);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(BACKWARD, delta);
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(RIGHT, delta);
        }
        // camera.Position.y = 0;
    }

    void cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
    {
        float ofstY = ypos - prevY;
        float ofstX = xpos - prevX;

        if (isFirstMouseMovement == true)
        {
            isFirstMouseMovement = false;
            prevY = ypos;
            prevX = xpos;
            return;
        }

        camera.ProcessMouseMovement(ofstX, -ofstY);
        prevY = ypos;
        prevX = xpos;
    }
};

#endif // FUOCO_APP_SCENE_H_
