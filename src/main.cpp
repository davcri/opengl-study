#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "fuoco_config.h"
#include "app/scene.h"

int vWidth = 800;
int vHeight = 600;

Scene *scene;

int main()
{
  std::cout << "Fuoco " << Fuoco_VERSION_MAJOR << "." << Fuoco_VERSION_MINOR
            << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  stbi_set_flip_vertically_on_load(true);

  GLFWwindow *window = glfwCreateWindow(vWidth, vHeight, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
  glEnable(GL_DEPTH_TEST);

  // ---
  scene = new Scene();
  glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos)
                           { scene->cursorPosCallback(window, xpos, ypos); });
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height)
      {
        vWidth = width;
        vHeight = height;
        glViewport(0, 0, width, height);
      });

  float prevElapsed = glfwGetTime();
  float delta = 0;

  while (!glfwWindowShouldClose(window))
  {
    float elapsed = glfwGetTime();
    delta = elapsed - prevElapsed;

    prevElapsed = elapsed;
    glClearColor(0.2, 0.2, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->processInput(window, delta);
    scene->update(vWidth, vHeight, delta);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
