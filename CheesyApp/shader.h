#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
  std::string vertexSource;
  std::string fragmentSource;
};

class Shader {
private:
  unsigned int mRendererId;
  std::string mFilepath;
  std::unordered_map<std::string, int> mUniformLocationCache;

public:
  Shader(const std::string &filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform4f(const std::string &name, float v0, float v1, float v2,
                    float v3);
  void setUniform1f(const std::string &name, float value);
  void setUniform1i(const std::string &name, int value);

private:
  int getUniformLocation(const std::string &name);
  unsigned int createShader(const std::string &vertexShader,
                            const std::string &fragmentShader);
  ShaderProgramSource parseShader(const std::string &filepath);
  unsigned int compileShader(unsigned int type, const std::string &source);
};