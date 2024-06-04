#pragma once
#include "appElement.h"
#include "game.h"
#include "imageRect.h"
#include "renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

struct Position {
  int x, y;

  Position(int sx, int sy) : x(sx), y(sy) {}
};

class App {
private:
  GLFWwindow *window;
  std::vector<AppElementInterface *> staticElements;
  std::vector<AppElementInterface *> pieceElements;
  std::vector<AppElementInterface *> highlightElements;
  int marginLeft = 0;
  // Game api;

public:
  App();
  ~App();

private:
  int initWindow(int width, int height, const char *title);
  void mainLoop();

  void tick(double delta);
  void draw();

  void initializeBoard();
  Position notationToPosition(char x, char y) const;
};