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

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(1100, 800, "Say Cheeseee", NULL, NULL);
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
  {
    ImageRect::initializeImageRects();

    float positions[] = {
        0.0f,   0.0f,   0.0f, 0.0f, // bottom left
        800.0f, 0.0f,   1.0f, 0.0f, // bottom right
        800.0f, 800.0f, 1.0f, 1.0f, // top right
        0.0f,   800.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    ImageRect boardImg("res/textures/board.png");

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window)) {
      renderer.clear();

      boardImg.draw(0, 0);

      if (r > 1.0f)
        increment = -0.05f;
      else if (r < 0)
        increment = 0.05f;
      r += increment;

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    ImageRect::deinitializeImageRects();
  }

  glfwTerminate();
  return 0;
}