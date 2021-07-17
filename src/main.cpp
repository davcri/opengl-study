#include "FuocoConfig.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  std::cout << "Fuoco " << Fuoco_VERSION_MAJOR << "." << Fuoco_VERSION_MINOR
            << std::endl;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  // glViewport(0, 0, 800, 600);
  glfwTerminate();

  return 0;
}