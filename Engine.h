#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2/SDL.h"
#include "stdio.h"

#include <vector>

typedef struct pair {
  int x;
  int y;
} pair_t;

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

  int snake_length;
  std::vector<pair_t> snake;
  int direction;
  int frame_count;

  pair_t apple;

  void move();
  void new_apple_position();

};

#endif
