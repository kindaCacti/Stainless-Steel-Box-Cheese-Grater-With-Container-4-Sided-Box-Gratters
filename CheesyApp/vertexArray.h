#pragma once
#include "indexBuffer.h"
#include "vertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
private:
  unsigned int mRendererId;

public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

  void bind() const;
  void unbind() const;
};