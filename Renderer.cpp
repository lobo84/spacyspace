#include "Renderer.h"


void Renderer::renderShip(const GameObject& ship, RenderWindow& window) {
  CircleShape shape(ship.getWidth()*2, 3);
  shape.setPosition(ship.getPos().getX()-ship.getWidth()*2, ship.getPos().getY());
  // set the shape color to green
  shape.setFillColor(Color(100, 250, 50));
  //  set a 10-pixel wide orange outline
  //  shape.setOutlineThickness(10);
  //  shape.setOutlineColor(Color(250, 150, 100));
  window.draw(shape);  
}

void Renderer::renderEnemyShip(const GameObject& ship, RenderWindow& window) {
  CircleShape shape(10);
  shape.setPosition(ship.getPos().getX(), ship.getPos().getY());
  // set the shape color to green
  shape.setFillColor(Color(100, 250, 50));
  // set a 10-pixel wide orange outline
  shape.setOutlineThickness(10);
  shape.setOutlineColor(Color(250, 150, 100));
  window.draw(shape);  
}

void Renderer::renderBullet(const GameObject& bullet, RenderWindow& window) {
  RectangleShape shape(Vector2f(bullet.getWidth(), bullet.getHeight()));
  auto halfWidth = bullet.getWidth()/2;
  auto halfHeight = bullet.getHeight()/2;
  shape.setPosition(bullet.getPos().getX(), bullet.getPos().getY());
  // set the shape color to green
  shape.setFillColor(Color(100, 250, 50));
  // set a 10-pixel wide orange outline
  //  shape.setOutlineThickness(10);
  shape.setOutlineColor(Color(250, 150, 100));
  window.draw(shape);  
}
#include <iostream>
void Renderer::render(RenderWindow& window, const World& world) {
  // clear the window with black color
  window.clear(Color::Black);
  Renderer::renderShip(world.getShip(), window);
  for (auto& e : world.getEnemies()) {
    Renderer::renderEnemyShip(*e, window);
  }
  cout << world.getBullets().size() << endl;
  for (auto& b : world.getBullets()) {
    Renderer::renderBullet(*b, window);
  }
  // draw everything here...
  // window.draw(...);
 
  // end the current frame
  window.display();
  
}
