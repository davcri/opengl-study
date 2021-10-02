#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "FuocoConfig.h"
#include "shader.h"
#include "cmath"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

float mixAmount = 0.5;

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
  {
    mixAmount += 0.01;
    mixAmount = std::min(1.0f, mixAmount);
  }
  else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    mixAmount -= 0.01;
    mixAmount = std::max(0.0f, mixAmount);
  }
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

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  // framebufferSizeCallback(window, 800, 600);

  float vertices[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f,    // top right
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // top left
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bot right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f}; // bot left

  unsigned int indices[] = {
      0, 1, 2,
      1, 2, 3};

  unsigned int VAO; // vertex array object
  glGenVertexArrays(1, &VAO);
  // bind Vertex Array Object
  glBindVertexArray(VAO);

  unsigned int VBO[1]; // vertex buffer object
  glGenBuffers(1, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // uv coordinates
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shader program("./shaders/shader.vert", "./shaders/shader.frag");

  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

  unsigned int texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  stbi_set_flip_vertically_on_load(true);

  // loading texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load("./assets/Preview.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
  }
  else
  {
    std::cout << "ERROR::Loading texture failed" << std::endl;
    return -1;
  }

  unsigned int texture2;
  glGenTextures(1, &texture2);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  int width2, height2, nrChannels2;
  unsigned char *data2 = stbi_load("./assets/awesomeface.png", &width2, &height2, &nrChannels2, 0);
  if (data2)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);
  }
  else
  {
    std::cout << "ERROR::Loading texture failed" << std::endl;
    return -1;
  }

  program.use();
  glUniform1i(glGetUniformLocation(program.id, "outTexture"), 0);
  glUniform1i(glGetUniformLocation(program.id, "outTexture2"), 1);

  bool setted = false;

  glm::mat4 xform = glm::mat4(1.0f);
  xform = glm::rotate(xform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  xform = glm::scale(xform, glm::vec3(1.5f, 1.5f, 1.5f));
  unsigned int transformLoc = glGetUniformLocation(program.id, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(xform));

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(0.2, 0.2, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float elapsed = glfwGetTime();
    program.setFloat("elapsed", elapsed);
    // program.setFloat("w", width);
    // program.setFloat("h", height);
    program.setFloat("mixAmount", mixAmount);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
