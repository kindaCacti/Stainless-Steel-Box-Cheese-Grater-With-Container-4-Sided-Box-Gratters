#pragma once
#include "appElement.h"
#include "bot.h"
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
  int x = 0;
  int y = 0;

  Position() = default;
  Position(int sx, int sy) : x(sx), y(sy) {}
};

class App {
public:
  static AppElementInterface *boardElement;
  static std::vector<AppElementInterface *> highlightElements;
  static std::vector<AppElementInterface *> pieceElements;
  static AppElementInterface *currentElement;
  static Position mousePos;
  static Game api;

private:
  GLFWwindow *window;
  int marginLeft = 0;

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

  void mouseButtonCallback(GLFWwindow *window, int button, int action,
                           int mods);
  static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                     double ypos);
  std::string getMove(int srcPosX, int srcPosY, int dstPosX, int dstPosY);

  bool moveCurrentElementTo(int x, int y);
};