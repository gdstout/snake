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

  void handle_events();
  void update();
  void render_screen();
  void terminate();

  bool running(){ return is_running; }

 private:
  bool is_running;
  SDL_Window* window;
  SDL_Renderer* renderer;

};

#endif
