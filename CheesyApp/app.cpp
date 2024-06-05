#include "app.h"
#include <stdexcept>

AppElementInterface *App::boardElement = nullptr;
std::vector<AppElementInterface *> App::highlightElements;
std::vector<AppElementInterface *> App::pieceElements;
Game App::api;
AppElementInterface *App::currentElement = nullptr;

std::string App::imgDir("res/textures/");
std::string App::imgDirWhite = App::imgDir + std::string("white/");
std::string App::imgDirBlack = App::imgDir + std::string("black/");
std::string App::imgNameBoard("Board.png");
std::string App::imgNamePawn("Pawn.png");
std::string App::imgNameRook("Rook.png");
std::string App::imgNameKnight("Knight.png");
std::string App::imgNameBishop("Bishop.png");
std::string App::imgNameQueen("Queen.png");
std::string App::imgNameKing("King.png");
std::string App::imgNameWin("Win.png");
std::string App::imgNameHighlight("highlight.png");

App::App() {
  if (initWindow(800, 800, "Say Cheeseee") == -1) {
    throw "Failed to initialize the app!";
  }
  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)&mouseButtonCallback);
  glfwSetCursorPosCallback(window, (GLFWcursorposfun)&cursorPositionCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  ImageRect::initializeImageRects();
  initializeBoard();

  gameLoop();
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

void App::initializeBoard() {
  boardElement =
      new AppElement<ImageRect>(new ImageRect(imgDir + imgNameBoard, 800, 800),
                                false, true, marginLeft, 0);

  for (int i = 0; i < 32; ++i) {
    highlightElements.push_back(new AppElement<ImageRect>(
        new ImageRect(imgDir + imgNameHighlight, 100, 100), false, true, 1000,
        1000));
  }

  int pawnRows[2] = {1, 6};
  int figureRows[2] = {0, 7};
  for (int c = 0; c < 2; ++c) {
    std::string dir(c == 0 ? imgDirWhite : imgDirBlack);
    for (int x = 0; x < 8; ++x) {
      pieceElements.push_back(new AppElement<ImageRect>(
          new ImageRect(dir + imgNamePawn, 100, 100), false, true,
          marginLeft + 100 * x, pawnRows[c] * 100));
    }
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameRook, 100, 100), false, true, marginLeft,
        figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameRook, 100, 100), false, true,
        marginLeft + 700, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameKnight, 100, 100), false, true,
        marginLeft + 100, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameKnight, 100, 100), false, true,
        marginLeft + 600, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameBishop, 100, 100), false, true,
        marginLeft + 200, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameBishop, 100, 100), false, true,
        marginLeft + 500, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameQueen, 100, 100), false, true,
        marginLeft + 300, figureRows[c] * 100));
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameKing, 100, 100), false, true,
        marginLeft + 400, figureRows[c] * 100));
  }
}

Position App::mousePos;
void App::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
  mousePos.x = xpos;
  mousePos.y = ypos;
}

void App::mouseButtonCallback(GLFWwindow *window, int button, int action,
                              int mods) {
  if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_RELEASE)
    return;

  int x = mousePos.x / 100;
  int y = (800 - mousePos.y) / 100;

  if (currentElement == nullptr) {
    updateCurrentElement(x, y);
    return;
  }

  bool success = moveCurrentElementTo(x, y);
  if (success) {
    Bot bot(api.getBoard());
    std::vector<int> mvs = bot.getBestMove(api.getRound(), 2);
    updateCurrentElement(mvs[0], 7 - mvs[1]);
    moveCurrentElementTo(mvs[2], 7 - mvs[3]);
    currentElement = nullptr;
    removeHighlights();
  } else {
    updateCurrentElement(x, y);
  }
}

void App::updateCurrentElement(int x, int y) {
  currentElement = nullptr;
  removeHighlights();
  for (auto element : pieceElements) {
    if (element->getX() == x * 100 && element->getY() == y * 100) {
      if (api.getBoard().at(x, 7 - y).color == api.turnOf()) {
        currentElement = element;
        updateHighlights();
      }
    }
  }
}

bool App::moveCurrentElementTo(int dstX, int dstY) {
  if (currentElement == nullptr)
    return false;

  int srcX = currentElement->getX() / 100;
  int srcY = currentElement->getY() / 100;
  std::string moveNot = movPosToNot(srcX, srcY, dstX, dstY);
  bool success = api.movePiece(moveNot.substr(0, 2), moveNot.substr(2, 2));
  if (!success)
    return false;

  removePieceAt(dstX, dstY);
  currentElement->setPos(dstX * 100, dstY * 100);

  Piece pieceInfo = api.getBoard().at(dstX, 7 - dstY);
  std::string dir(pieceInfo.color == PIECE_COLOR::WHITE ? imgDirWhite
                                                        : imgDirBlack);

  // promotion check
  bool promotionOccurred =
      pieceInfo.name == PIECE_NAMES::QUEEN && pieceInfo.moves_done == -1;
  if (promotionOccurred) {
    removePieceAt(dstX, dstY);
    pieceElements.push_back(
        new AppElement<ImageRect>(new ImageRect(dir + imgNameQueen, 100, 100),
                                  false, true, dstX * 100, dstY * 100));
  }

  // castling check
  bool isKing = pieceInfo.name == PIECE_NAMES::KING;
  if (isKing) {
    Piece toCheck[2] = {api.getBoard().at(dstX + 1, 7 - dstY),
                        api.getBoard().at(dstX - 1, 7 - dstY)};
    for (int i = 0; i < 2; ++i) {
      Piece &c = toCheck[i];
      if (c.name == PIECE_NAMES::ROOK && c.moves_done == -1 &&
          c.color != api.turnOf()) {
        for (auto element : pieceElements) {
          if (element->getX() == 0 + (700 * i) &&
              element->getY() == dstY * 100) {
            element->setPos(dstX * 100 + 100 - (200 * i), dstY * 100);
            break;
          }
        }
        break;
      }
    }
  }

  return true;
}

void App::removePieceAt(int x, int y) {
  for (int i = 0; i < pieceElements.size(); ++i) {
    if (pieceElements[i]->getX() / 100 == x &&
        pieceElements[i]->getY() / 100 == y) {
      delete pieceElements[i];
      pieceElements.erase(pieceElements.begin() + i);
    }
  }
}

void App::removeHighlights() {
  for (auto element : highlightElements) {
    element->setPos(1000, 1000);
  }
}

void App::updateHighlights() {
  removeHighlights();
  int x = currentElement->getX();
  int y = currentElement->getY();
  highlightElements[0]->setPos(x, y);
  api.choosePiece((x / 100) + 'a', (y / 100) + '1');
  api.loadPossibleMoves();
  auto moves = api.getPossibleMoves();
  for (int i = 0; i < moves.size(); ++i) {
    auto &m = moves[i];
    highlightElements[i + 1]->setPos(x + m.delta_x * 100, y - m.delta_y * 100);
  }
}

bool App::checkIfEnded() {
  if (api.isEnd(std::cout)) {
    std::string dir(api.turnOf() == PIECE_COLOR::WHITE ? imgDirBlack
                                                       : imgDirWhite);
    pieceElements.push_back(new AppElement<ImageRect>(
        new ImageRect(dir + imgNameWin, 800, 400), false, true, 0, 200));
    return true;
  }
  return false;
}

std::string App::movPosToNot(int srcPosX, int srcPosY, int dstPosX,
                             int dstPosY) {
  std::string result;
  result += ('a' + srcPosX);
  result += ('1' + srcPosY);
  result += ('a' + dstPosX);
  result += ('1' + dstPosY);
  return result;
}

int App::initWindow(int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

void App::gameLoop() {
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