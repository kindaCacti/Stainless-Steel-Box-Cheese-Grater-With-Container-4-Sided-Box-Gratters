#pragma once
#include "renderer.h"
#include <string>

class Texture {
private:
  unsigned int mRendererId;
  std::string mFilepath;
  unsigned char *mLocalBuffer;
  int mWidth, mHeight, mBPP;

public:
  Texture(const std::string &filepath);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidth() const { return mWidth; }
  inline int getHeight() const { return mHeight; }
};