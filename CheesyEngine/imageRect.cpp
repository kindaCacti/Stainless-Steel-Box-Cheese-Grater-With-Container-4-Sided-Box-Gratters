#include "imageRect.h"
#include "renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"

unsigned int ImageRect::indices[6] = {
    // to make a square
    0, 1, 2, // bottom right triangle
    2, 3, 0  // top left triangle
};
Renderer *ImageRect::renderer = nullptr;
IndexBuffer *ImageRect::indexBuffer = nullptr;
Shader *ImageRect::shader = nullptr;

void ImageRect::initializeImageRects() {
  ImageRect::renderer = new Renderer();
  ImageRect::indexBuffer = new IndexBuffer(ImageRect::indices, 6);
  ImageRect::shader = new Shader("res/shaders/basic.glsl");
}

void ImageRect::deinitializeImageRects() {
  delete ImageRect::renderer;
  delete ImageRect::indexBuffer;
  delete ImageRect::shader;
}

ImageRect::ImageRect(const std::string &filepath, unsigned int width,
                     unsigned int height)
    : texture(filepath), mWidth(width), mHeight(height) {
  if (!renderer || !indexBuffer || !shader) {
    std::cout << "Required static variables of ImageRect not initialized! Use "
                 "'ImageRect::initializeImageRects()' to do so."
              << std::endl;
  }
  // Calculating vertices
  if (width == 0)
    mWidth = texture.getWidth();
  if (height == 0)
    mHeight = texture.getHeight();
  float positions[] = {
      0.0f,          0.0f,           0.0f, 0.0f, // bottom left
      (float)mWidth, 0.0f,           1.0f, 0.0f, // bottom right
      (float)mWidth, (float)mHeight, 1.0f, 1.0f, // top right
      0.0f,          (float)mHeight, 0.0f, 1.0f  // top left
  };

  // Loading vertices
  VertexBuffer vb(positions, 4 * 4 * sizeof(float));
  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);
  vertexArray.AddBuffer(vb, layout);

  // Calculating transformation
  int w, h;
  glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
  projectionMatrix = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);

  // Setting shader uniforms
  shader->bind();
  shader->setUniformMat4f("uMVP", projectionMatrix);

  texture.bind();
  shader->setUniform1i("uTexture", 0);

  vertexArray.unbind();
  vb.unbind();
  indexBuffer->unbind();
  shader->unbind();
}

ImageRect::~ImageRect() {}

void ImageRect::draw(int x, int y) {
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
  shader->bind();
  shader->setUniformMat4f("uMVP", projectionMatrix * trans);
  texture.bind();
  shader->setUniform1i("uTexture", 0);
  shader->unbind();
  renderer->draw(vertexArray, *indexBuffer, *shader);
}