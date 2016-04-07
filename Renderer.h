#ifndef RENDERER_H
#define RENDERER_H

#include "World.h"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Renderer {
 public:
  static void render(RenderWindow& window, const World& world);
 private:
  static void renderShip(const GameObject& ship, RenderWindow& window);
  static void renderEnemyShip(const GameObject& ship, RenderWindow& window);
  static void renderBullet(const GameObject& bullet, RenderWindow& window);
};

#endif
