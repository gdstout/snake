#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2/SDL.h"
#include "stdio.h"

class Engine {
 public:
  Engine();
  ~Engine();

  void init(const char* title, int x_pos, int y_pos, int width, int height,
	    bool fullscreen);

  void handleEvents();
  void update();
  void renderScreen();
  void end();

  bool is_running();

 private:
  bool is_running();
  SDL_Window* window;
  SDL_Renderer* renderer;
};

#endif
