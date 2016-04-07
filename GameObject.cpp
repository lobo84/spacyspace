#include "GameObject.h"
#include <algorithm>
using namespace std;

GameObject::GameObject(const Vector2D<float>& pos,
		       const Vector2D<float>& dir,
		       int width,
		       int height,
		       float speed) :
  mPos(pos), mDir(dir), mWidth(width), mHeight(height), mSpeed(speed) {
}

Vector2D<float> GameObject::getPos() const {
  return mPos;
}

int GameObject::getWidth() const {
  return mWidth;
}

int GameObject::getHeight() const {
  return mHeight;
}

void GameObject::setDir(const Vector2D<float>& dir) {
  mDir = dir;
}

bool GameObject::isInside(int x, int y, int width, int height) {
  return mPos.getX() >= x && mPos.getX() <= width &&
         mPos.getY() >= y && mPos.getY() <= height;
}

bool GameObject::checkCollision(const GameObject& other) const {
  auto halfWidth1 = mWidth/2;
  auto x1Start = mPos.getX() - halfWidth1;   
  auto x1End = mPos.getX() + halfWidth1;

  auto halfHeight1 = mHeight/2;
  auto y1Start = mPos.getY() - halfHeight1;   
  auto y1End = mPos.getY() + halfHeight1;

  auto halfWidth2 = other.mWidth/2;
  auto x2Start = other.getPos().getX() - halfWidth2;   
  auto x2End = other.getPos().getX() + halfWidth2;

  auto halfHeight2 = other.mHeight/2;
  auto y2Start = other.getPos().getY() - halfHeight2;   
  auto y2End = other.getPos().getY() + halfHeight2;

  return (x1Start < x2End && x1End > x2Start &&
	  y1Start < y2End && y1End > y2Start );  
}

Vector2D<float> GameObject::getDir() const {
  return mDir;
}

void GameObject::move(int elapsedMsec) {
  static const float speedFactor {1.0};

  Vector2D<float> addPos = mDir * speedFactor * mSpeed * elapsedMsec;

  mPos = mPos + addPos;
}
