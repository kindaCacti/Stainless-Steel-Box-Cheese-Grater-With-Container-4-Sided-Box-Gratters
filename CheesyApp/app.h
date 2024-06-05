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

  static std::string imgDir;
  static std::string imgDirWhite;
  static std::string imgDirBlack;
  static std::string imgNameBoard;
  static std::string imgNamePawn;
  static std::string imgNameRook;
  static std::string imgNameKnight;
  static std::string imgNameBishop;
  static std::string imgNameQueen;
  static std::string imgNameKing;
  static std::string imgNameWin;
  static std::string imgNameHighlight;

private:
  GLFWwindow *window;
  int marginLeft = 0;

public:
  App();
  ~App();

private:
  int initWindow(int width, int height, const char *title);
  void gameLoop();

  void tick(double delta);
  void draw();

  void initializeBoard();

  static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                     double ypos);
  void mouseButtonCallback(GLFWwindow *window, int button, int action,
                           int mods);

  void updateCurrentElement(int x, int y);
  bool moveCurrentElementTo(int x, int y);
  void removePieceAt(int x, int y);
  void removeHighlights();
  void updateHighlights();
  bool checkIfEnded();
  std::string movPosToNot(int srcPosX, int srcPosY, int dstPosX, int dstPosY);
};