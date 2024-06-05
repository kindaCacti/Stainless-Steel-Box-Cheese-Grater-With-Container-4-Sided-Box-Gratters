#include "app.h"
#include <stdexcept>

AppElementInterface *App::boardElement = nullptr;
std::vector<AppElementInterface *> App::highlightElements;
std::vector<AppElementInterface *> App::pieceElements;
Game App::api;
AppElementInterface *App::currentElement = nullptr;
App::App() {
  if (initWindow(800, 800, "Say Cheeseee") == -1) {
    throw "Failed to initialize the app!";
  }
  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)&mouseButtonCallback);
  glfwSetCursorPosCallback(window, (GLFWcursorposfun)&cursorPositionCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  ImageRect::initializeImageRects();
  initializeBoard();

  mainLoop();
}

void App::initializeBoard() {
  boardElement = new AppElement<ImageRect>(
      new ImageRect("res/textures/board.png", 800, 800), false, true,
      marginLeft, 0);

  for (int i = 0; i < 32; ++i) {
    highlightElements.push_back(new AppElement<ImageRect>(
        new ImageRect("res/textures/highlight.png", 100, 100), false, true,
        1000, 1000));
  }

  int pawnRows[2] = {1, 6};
  int figureRows[2] = {0, 7};
  for (int c = 0; c < 2; ++c) {
    std::string color(c == 0 ? "white" : "black");
    std::string path = std::string("res/textures/") + color;
    for (int x = 0; x < 8; ++x) {
      pieceElements.push_back(new AppElement<ImageRect>(
          new ImageRect(path + std::string("/Pawn.png"), 100, 100), false, true,
          marginLeft + 100 * x, pawnRows[c] * 100));
    }
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Rook.png"), 100, 100), false, true,
        marginLeft, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Rook.png"), 100, 100), false, true,
        marginLeft + 700, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Knight.png"), 100, 100), false, true,
        marginLeft + 100, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Knight.png"), 100, 100), false, true,
        marginLeft + 600, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Bishop.png"), 100, 100), false, true,
        marginLeft + 200, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Bishop.png"), 100, 100), false, true,
        marginLeft + 500, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/Queen.png"), 100, 100), false, true,
        marginLeft + 300, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(path + std::string("/King.png"), 100, 100), false, true,
        marginLeft + 400, figureRows[c] * 100));
  }
}

Position App::notationToPosition(char x, char y) const {
  return Position(int(x - 'a') * 100, int(y - '1') * 100);
}

void App::tick(double delta) {}

void App::draw() {
  if (boardElement)
    boardElement->draw();
  for (auto element : highlightElements) {
    element->draw();
  }
  for (auto element : pieceElements) {
    element->draw();
  }
}

void App::mouseButtonCallback(GLFWwindow *window, int button, int action,
                              int mods) {
  if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_RELEASE)
    return;

  int x = mousePos.x / 100 * 100;
  int y = (800 - mousePos.y) / 100 * 100;

  if (currentElement != nullptr) {
    auto move = getMove(currentElement->getX() / 100,
                        currentElement->getY() / 100, x / 100, y / 100);
    bool result = api.movePiece(move.substr(0, 2), move.substr(2, 2));
    if (result) {
      for (int i = 0; i < pieceElements.size(); ++i) {
        if (pieceElements[i]->getX() == x && pieceElements[i]->getY() == y) {
          delete pieceElements[i];
          pieceElements.erase(pieceElements.begin() + i);
        }
      }
      currentElement->setPos(x, y);
      bool promotion = api.getBoard().at(x / 100, 7 - y / 100).moves_done == -1;
      if (promotion) {
        for (int i = 0; i < pieceElements.size(); ++i) {
          if (pieceElements[i] == currentElement) {
            delete currentElement;
            std::string color(api.getBoard().at(x / 100, 7 - y / 100).color ==
                                      PIECE_COLOR::WHITE
                                  ? "white"
                                  : "black");
            std::string path = std::string("res/textures/") + color;
            pieceElements[i] = new AppElement<ImageRect>(
                new ImageRect(path + std::string("/Queen.png"), 100, 100),
                false, true, x, y);
            break;
          }
        }
      }

      if (api.isEnd(std::cout)) {
        std::string color(api.turnOf() == PIECE_COLOR::WHITE ? "black"
                                                             : "white");
        std::string path = std::string("res/textures/") + color;
        path += "/Wins.png";
        pieceElements.push_back(new AppElement<ImageRect>(
            new ImageRect(path, 800, 400), false, true, 0, 200));
      }
    }
    for (auto element : highlightElements) {
      element->setPos(1000, 1000);
    }
    currentElement = nullptr;
  }

  for (auto element : pieceElements) {
    if (element->getX() == x && element->getY() == y) {
      currentElement = element;
      if (api.getBoard().at(x / 100, 7 - y / 100).color == api.turnOf()) {
        highlightElements[0]->setPos(x, y);
        api.choosePiece((x / 100) + 'a', (y / 100) + '1');
        api.loadPossibleMoves();
        auto moves = api.getPossibleMoves();
        for (int i = 0; i < moves.size(); ++i) {
          auto &m = moves[i];
          highlightElements[i + 1]->setPos(x + m.delta_x * 100,
                                           y - m.delta_y * 100);
        }
      }
    }
  }
}

std::string App::getMove(int srcPosX, int srcPosY, int dstPosX, int dstPosY) {
  std::string result;
  result += ('a' + srcPosX);
  result += ('1' + srcPosY);
  result += ('a' + dstPosX);
  result += ('1' + dstPosY);
  return result;
}

Position App::mousePos;
void App::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
  mousePos.x = xpos;
  mousePos.y = ypos;
}

void App::mainLoop() {
  Renderer renderer;
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    double now = glfwGetTime();
    double delta = now - lastTime;
    lastTime = now;

    renderer.clear();

    tick(delta);
    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

int App::initWindow(int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
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

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  return 0;
}

App::~App() {
  delete boardElement;
  for (auto element : highlightElements) {
    delete element;
  }
  highlightElements.clear();
  for (auto element : pieceElements) {
    delete element;
  }
  pieceElements.clear();
  ImageRect::deinitializeImageRects();
  glfwTerminate();
}