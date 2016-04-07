#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
using namespace std;
template <class T>
class Vector2D {
public:

  Vector2D(T x, T y) {
    mX = x;
    mY = y;
  };
  
  T getX() const {
    return mX;
  };
  
  T getY() const {
    return mY;
  };

  void setX(T x) {
    mX = x;
  };
  
  void setY(T y) {
    mY = y;
  };

  template <class B>
  Vector2D<T> operator+(const Vector2D<B>& rhs) {
    mX += rhs.mX;
    mY += rhs.mY;
    return *this;
  };

  template <class B>
  Vector2D<T> operator-(const Vector2D<B>& rhs) {
    mX -= rhs.mX;
    mY -= rhs.mY;
    return *this;
  };

  template <class C>
  Vector2D<T> operator*(const C& rhs) {
    mX *= rhs;
    mY *= rhs;
    return *this;
  };

  void print() const {
    cout << mX << "," << mY << endl;
  }
  
private:
  T mX;
  T mY;
};

#endif
