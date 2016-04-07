#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Input.h"
#include "World.h"

#include <memory>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
  // create the window
  static const int Width = 800;
  static const int Height = 640;
  
  Input input;
  World world(Width, Height);
  RenderWindow window(VideoMode(Width, Height), "game window");
  Clock clock;
  
  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
    Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == Event::Closed)
	window.close();
    }	
    input.update();
    int elapsed = clock.restart().asMilliseconds();
    sleep(milliseconds(16-elapsed));
    //    cout << elapsed << endl;
    world.update(input, elapsed);
    Renderer::render(window,world);	
  }
  
  return 0;
}
