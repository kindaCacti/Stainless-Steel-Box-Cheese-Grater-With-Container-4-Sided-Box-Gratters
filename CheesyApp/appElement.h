#pragma once

class AppElementInterface {

protected:
  bool mDrawable;
  bool mTickable;
  int mX, mY = 0;

public:
  AppElementInterface(bool tickable, bool drawable, int x = 0, int y = 0)
      : mTickable(tickable), mDrawable(drawable), mX(x), mY(y) {}
  virtual ~AppElementInterface() {}

  virtual AppElementInterface &operator=(AppElementInterface *other) {
    return *this;
  };

  virtual void setX(int x) {}
  virtual void setY(int y) {}
  virtual int getX() {}
  virtual int getY() {}
  virtual void setPos(int x, int y) {}

  virtual void tick(double delta) {}
  virtual void draw() {}
};

template <typename T> class AppElement : public AppElementInterface {
private:
  T *mElement;

public:
  AppElement(T *element, bool tickable, bool drawable, int x = 0, int y = 0)
      : mElement(element), AppElementInterface(tickable, drawable, x, y) {}
  ~AppElement() { delete mElement; }

  AppElement &operator=(AppElement *other) {
    delete mElement;
    this = other;
    return *this;
  }

  void setX(int x) { mX = x; }
  void setY(int y) { mY = y; }
  int getX() { return mX; }
  int getY() { return mY; }
  void setPos(int x, int y) {
    mX = x;
    mY = y;
  }

  void tick(double delta) {
    if (mTickable)
      mElement->tick(delta);
  }
  void draw() {
    if (mDrawable)
      mElement->draw(mX, mY);
  }

  T &operator*() { return *mElement; }
};