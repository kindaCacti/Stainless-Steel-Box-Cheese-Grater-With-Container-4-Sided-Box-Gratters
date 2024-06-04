#include "imageRect.h"
#include "indexBuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int init(GLFWwindow *&window, int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  return 0;
}

int main() {
  GLFWwindow *window;
  if (init(window, 1100, 800, "Say Cheeseee") == -1)
    return -1;
  {
    ImageRect::initializeImageRects();
    ImageRect boardImg("res/textures/board.png");
    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {
      renderer.clear();
      boardImg.draw(10, 10);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
    ImageRect::deinitializeImageRects();
  }
  glfwTerminate();
  return 0;
}