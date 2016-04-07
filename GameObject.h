#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector2D.h"
class GameObject {

 public:
  GameObject(const Vector2D<float>& pos,const Vector2D<float>& dir, int width, int height, float speed = 1);
  Vector2D<float> getPos() const;
  Vector2D<float> getDir() const;
  void move(int elapsedMsec);
  void setDir(const Vector2D<float>& dir);
  bool checkCollision(const GameObject& other) const;
  bool isInside(int x, int y, int width, int height);
  int getWidth() const;
  int getHeight() const;
  
 private:
  GameObject();

  Vector2D<float> mPos;
  Vector2D<float> mDir;
  int mWidth;
  int mHeight;
  float mSpeed;
};

#endif
