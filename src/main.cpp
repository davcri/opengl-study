#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "FuocoConfig.h"
#include "shader.h"
#include "cmath"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "./camera.h"

#include <assimp/Importer.hpp>
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// #include "Mesh.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

int vWidth = 800;
int vHeight = 600;

bool isFirstMouseMovement = true;
float prevY = 0.0f;
float prevX = 0.0f;
float delta;
float fov = 50.0f;

Camera camera = Camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0));

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, vWidth, vHeight);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  // framebufferSizeCallback(window, 800, 600);

  float vertices[] = {
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

  unsigned int VAO; // vertex array object
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO[1]; // vertex buffer object
  glGenBuffers(1, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
  glEnableVertexAttribArray(2);

  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // diffuse map
  glActiveTexture(GL_TEXTURE0);
  float textureDiffuseMapId = loadTexture("./assets/container2.png");
  glActiveTexture(GL_TEXTURE1);
  float textureSpecularMapId = loadTexture("./assets/container2_specular.png");
  // emission map
  // glActiveTexture(GL_TEXTURE2);
  // loadTexture("./assets/matrix.jpg");

  Shader objShader("./shaders/shader.vert", "./shaders/shader.frag");
  Shader lightShader("./shaders/light.vert", "./shaders/light.frag");

  glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
  glEnable(GL_DEPTH_TEST);

  glm::mat4 model = glm::mat4(1.0f);
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)};

  // lights
  glm::vec3 lightPos(2.0f, 0.0f, 0.0f);
  glm::vec3 lightCol(1.0f, 1.0f, 1.0f);

  glm::vec3 pointLightPositions[] = {
      glm::vec3(0.7f - 2.0f, 0.2f, 2.0f),
      glm::vec3(2.3f - 2.0f, -3.3f, -4.0f),
      glm::vec3(-4.0f - 2.0f, 2.0f, -12.0f),
      glm::vec3(0.0f - 2.0f, 0.0f, -3.0f)};

  objShader.use();
  objShader.setVec3("dirLight.direction", -lightPos);
  objShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
  objShader.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f); // darken diffuse light a bit
  objShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

  for (int i = 0; i < 4; i++)
  {
    objShader.use();
    char buffer[64];
    sprintf(buffer, "pointLights[%i].position", i);
    objShader.setVec3(buffer, pointLightPositions[i]);
    sprintf(buffer, "pointLights[%i].constant", i);
    objShader.setFloat(buffer, 1.0);
    sprintf(buffer, "pointLights[%i].linear", i);
    objShader.setFloat(buffer, 0.08f);
    sprintf(buffer, "pointLights[%i].quadratic", i);
    objShader.setFloat(buffer, 0.0032f);

    sprintf(buffer, "pointLights[%i].ambient", i);
    objShader.setVec3(buffer, 0.15f, 0.15f, 0.15f);
    sprintf(buffer, "pointLights[%i].diffuse", i);
    objShader.setVec3(buffer, 0.75f, 0.75f, 0.75f);
    sprintf(buffer, "pointLights[%i].specular", i);
    objShader.setVec3(buffer, 1.0f, 1.0f, 1.0f);
  }

  // objShader.setVec3("light.direction", camera.Front);
  // objShader.setFloat("light.cutoff", glm::cos(glm::radians(20.0f)));
  // objShader.setFloat("light.outerCutoff", glm::cos(glm::radians(15.0f)));
  // objShader.setVec3("light.direction", -lightPos);

  objShader.setVec3("material.ambient", 0.5f, 0.5f, 0.31f);
  objShader.setVec3("material.diffuse", 0.5f, 0.5f, 0.31f);
  objShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
  objShader.setFloat("material.shininess", 1.0f);
  objShader.setInt("material.diffuseMap", 0);
  objShader.setInt("material.specularMap", 1);

  lightShader.use();
  lightShader.setVec3("lightPos", lightPos);

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

    // cubes
    objShader.use();
    glBindVertexArray(VAO);
    objShader.setFloat("elapsed", elapsed);
    objShader.setVec3("light.position", camera.Position);
    objShader.setVec3("light.direction", camera.Front);
    objShader.setMat4("view", view);
    objShader.setVec3("viewPos", camera.Position);
    objShader.setMat4("proj", proj);
    for (unsigned int i = 0; i < 10; i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = elapsed * 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      objShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    for (int i = 0; i < 4; i++)
    {
      lightShader.use();
      glBindVertexArray(lightVAO);
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.15f));
      lightShader.setMat4("view", view);
      lightShader.setMat4("proj", proj);
      lightShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
