#include "Engine.h"


Engine* engine = NULL;
const int WIDTH = 450;
const int HEIGHT = 450;

int main(int argc, char* argv[]){
  const int FPS = 60;
  const int f_delay = 1000/FPS;

  uint32_t f_start;
  int f_time;
  
  engine = new Engine();

  engine->init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
	       HEIGHT, false);

  while(engine->running()){

    f_start = SDL_GetTicks();
    
    engine->handle_events();
    engine->update();
    engine->render_screen();

    f_time = SDL_GetTicks() - f_start;

    /* limit game speed to 60 fps */
    if(f_delay > f_time){
      SDL_Delay(f_delay - f_time);
      }
  }

  engine->terminate();
  
  return 0;
}
