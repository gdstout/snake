#include "Engine.h"


Engine* engine = NULL;
const int WIDTH = 400;
const int HEIGHT = 400;

int main(int argc, char* argv[]){
  engine = new Engine();

  engine->init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
	       HEIGHT, false);

  while(engine->running()){
    engine->handle_events();
    engine->update();
    engine->render_screen();
    SDL_Delay(500);
  }

  engine->terminate();
  
  return 0;
}
