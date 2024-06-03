#include <iostream>
#include <windows.h>
#include <GLFW/glfw3.h>


int main() {
  if(!glfwInit()) {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(640,480,"Hello Window",NULL,NULL);

  if(window == NULL) {
    std::cout << "Window could not be created!\n";
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}