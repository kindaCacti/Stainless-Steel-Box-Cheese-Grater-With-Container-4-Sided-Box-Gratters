#pragma once
#include "indexBuffer.h"
#include "texture.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include <GLFW/glfw3.h>
#include <string>

class ImageRect {
private:
  unsigned int mWidth;
  unsigned int mHeight;
  VertexArray vertexArray;
  Texture texture;

public:
  // Needs to be executed in context for imageRects to work:
  static void initializeImageRects();
  // Needs to be executed in context for static fields to be cleaned:
  static void deinitializeImageRects();

  static unsigned int indices[6]; // indices to make a square
  static IndexBuffer *indexBuffer;
  static Shader *shader;
  static Renderer *renderer;

  ImageRect(const std::string &filepath);
  ImageRect(const std::string &filepath, int width, int height);
  ~ImageRect();

  void draw(int x, int y);
  void draw(int x, int y, unsigned int width, unsigned int height);

private:
  GLFWvidmode getWindowSize();
};