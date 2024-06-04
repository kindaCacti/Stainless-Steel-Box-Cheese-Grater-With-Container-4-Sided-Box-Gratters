#pragma once
#include "indexBuffer.h"
#include "shader.h"
#include "vertexArray.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __debugbreak();
#define GLCall(x)                                                              \
  glClearError();                                                              \
  x;                                                                           \
  ASSERT(glLogCall(#x, __FILE__, __LINE__));

void glClearError();
bool glLogCall(const char *function, const char *file, int line);

#include <GL/glew.h>

#define ASSERT(x)

class Renderer {

public:
  void clear();
  void draw(const VertexArray &va, const IndexBuffer &ib,
            const Shader &shader) const;
};