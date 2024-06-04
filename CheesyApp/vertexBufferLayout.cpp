#include "vertexBufferLayout.h"

template<>
void VertexBufferLayout::push<float>(unsigned int count) {
  mElements.push_back({ GL_FLOAT, count, GL_FALSE });
  mStride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
  mElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  mStride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count) {
  mElements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
  mStride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);;
}