#include "shader.h"
#include "fstream"
#include "renderer.h"
#include "sstream"

Shader::Shader(const std::string &filepath) : mFilepath(filepath) {
  ShaderProgramSource source = parseShader(filepath);
  mRendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() { GLCall(glDeleteProgram(mRendererId)); }

void Shader::bind() const { GLCall(glUseProgram(mRendererId)); }

void Shader::unbind() const { GLCall(glUseProgram(0)); }

void Shader::setUniform1i(const std::string &name, int value) {
  GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string &name, float value) {
  GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
  GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
  GLCall(glUniformMatrix4fv(getUniformLocation("uMVP"), 1, GL_FALSE,
                            &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string &name) {
  if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
    return mUniformLocationCache[name];
  GLCall(int location = glGetUniformLocation(mRendererId, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: uniform '" << name << "' doesn't exist!"
              << std::endl;
  }
  mUniformLocationCache[name] = location;
  return location;
}

unsigned int Shader::createShader(const std::string &vertexShader,
                                  const std::string &fragmentShader) {
  GLCall(unsigned int program = glCreateProgram());
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

ShaderProgramSource Shader::parseShader(const std::string &filepath) {
  std::ifstream stream(filepath);
  if (!stream.is_open()) {
    std::cout << "Couldn't find specified shader file: '" << filepath << "'!"
              << std::endl;
  }

  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
  ShaderType type = ShaderType::NONE;

  std::string line;
  std::stringstream ss[2];
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(unsigned int type,
                                   const std::string &source) {
  GLCall(unsigned int id = glCreateShader(type));
  const char *src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char *message = (char *)alloca(length * sizeof(length));
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader!" << std::endl;
    std::cout << message << std::endl;
    GLCall(glDeleteShader(id));
    return 0;
  }
  return id;
}