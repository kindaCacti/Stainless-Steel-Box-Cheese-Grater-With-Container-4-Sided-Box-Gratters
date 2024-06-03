#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __debugbreak();
#define GLCall(x)                                                              \
  glClearError();                                                              \
  x;                                                                           \
  ASSERT(glLogCall(#x, __FILE__, __LINE__));

static void glClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

static bool glLogCall(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file
              << ":" << line << std::endl;
    return false;
  }
  return true;
}

struct ShaderProgramSource {
  std::string vertexSource;
  std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string &filepath) {
  std::ifstream stream(filepath);

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

static unsigned int compileShader(unsigned int type,
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

static unsigned int createShader(const std::string &vertexShader,
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

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(1100, 750, "Say Cheeseee", NULL, NULL);
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

  float positions[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  unsigned int buffer;
  GLCall(glGenBuffers(1, &buffer));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
  GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions,
                      GL_STATIC_DRAW));

  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                               (const void *)0));

  unsigned int ibo;
  GLCall(glGenBuffers(1, &ibo));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
                      indices, GL_STATIC_DRAW));

  ShaderProgramSource source = parseShader("CheesyApp/shaders/Basic.shader");
  unsigned int shader =
      createShader(source.vertexSource, source.fragmentSource);
  GLCall(glUseProgram(shader));

  GLCall(int location = glGetUniformLocation(shader, "uColor"));
  ASSERT(location != -1);
  GLCall(glUniform4f(location, 0.5f, 1.0f, 0.5f, 1.0f));

  float r = 0.0f;
  float increment = 0.05f;

  while (!glfwWindowShouldClose(window)) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    GLCall(int location = glGetUniformLocation(shader, "uColor"));
    GLCall(glUniform4f(location, r, 1.0f, 0.5f, 1.0f));
    if (r > 1.0f)
      increment = -0.05f;
    else if (r < 0)
      increment = 0.05f;
    r += increment;

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  GLCall(glDeleteProgram(shader));

  glfwTerminate();
  return 0;
}