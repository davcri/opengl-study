#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "FuocoConfig.h"
#include "modules/shader.h"
#include "modules/camera.h"
#include "modules/Model.h"
#include "modules/textures.h"

int vWidth = 800;
int vHeight = 600;

bool isFirstMouseMovement = true;
float prevY = 0.0f;
float prevX = 0.0f;
float delta;
float fov = 50.0f;

Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0));

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  vWidth = width;
  vHeight = height;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
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

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
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

int main()
{
  std::cout << "Fuoco " << Fuoco_VERSION_MAJOR << "." << Fuoco_VERSION_MINOR
            << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(vWidth, vHeight, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // glViewport(0, 0, vWidth, vHeight);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  TextureLoader textureLoader(true);

  Model modelFromAssimp("./assets/backpack/backpack.obj");
  // Shader lightShader("./shaders/light.vert", "./shaders/light.frag");
  Shader modelShader("./shaders/shader.vert", "./shaders/shader.frag");

  modelShader.use();

  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
  glEnable(GL_DEPTH_TEST);

  // lights
  // glm::vec3 lightPos(2.0f, 0.0f, 0.0f);
  // glm::vec3 lightCol(1.0f, 1.0f, 1.0f);
  // lightShader.use();
  // lightShader.setVec3("lightPos", lightPos);
  camera.Front = glm::vec3(0.0f, 0.0, -1.0f);
  glm::mat4 view = camera.GetViewMatrix();
  float prevElapsed = glfwGetTime();

  while (!glfwWindowShouldClose(window))
  {
    float elapsed = glfwGetTime();
    delta = elapsed - prevElapsed;
    processInput(window);
    prevElapsed = elapsed;
    glClearColor(0.2, 0.2, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // projection
    glm::mat4 proj = glm::perspective(glm::radians(fov), (float)vWidth / (float)vHeight, 0.1f, 100.0f);
    proj = glm::perspective(glm::radians(fov), (float)vWidth / (float)vHeight, 0.01f, 100.0f);
    view = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    modelShader.use();
    modelShader.setMat4("model", model);
    modelShader.setMat4("view", view);
    modelShader.setMat4("proj", proj);

    modelFromAssimp.Draw(modelShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
