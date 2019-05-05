#include "Engine.h"
#include <iostream>

Engine::Engine(){}
Engine::~Engine(){}

void Engine::init(const char* title, int x_pos, int y_pos, int width,
		  int height, bool fullscreen){
  int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;
  
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

    std::cout << "SDL initialized..." << std::endl;
    
    window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
    if(window){
      std::cout << "Window created..." << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer){
      std::cout << "Renderer created..." << std::endl;
    }

    is_running = true;
  }else{
    is_running = false;
  }
}

void Engine::handle_events(){
  SDL_Event event;
  SDL_PollEvent(&event);
  
  switch(event.type){
  case SDL_QUIT:
    is_running = false;
    break;

  default:
    break;
  }
}

void Engine::update(){
  
}

void Engine::render_screen(){
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

void Engine::terminate(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}
