#include "Input.h"
#include <SFML/Graphics.hpp>

bool Input::getUp() const{
  return up;
}

bool Input::getDown() const {
  return down;
}

bool Input::getLeft() const {
  return left;
}

bool Input::getRight() const {
  return right;
}

bool Input::getSpace() const {
  return space;
}

void Input::update() {
  left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
  right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
  up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
  down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
  space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);  
}
