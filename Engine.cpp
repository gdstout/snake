#include "Engine.h"
#include <iostream>

Engine::Engine(){}
Engine::~Engine(){}

void render_walls(SDL_Renderer* r){
  SDL_Rect rect;

  SDL_SetRenderDrawColor(r, 232, 232, 232, 255);

  rect.w = 13;
  rect.h = 13;
  
  for(int i = 0; i < 30; i ++){
    for(int j = 0; j < 30; j ++){
      if(i == 0 || j == 0 || i == 29 || j == 29){
	rect.x = (j * 15) + 1;
	rect.y = (i * 15) + 1;
	SDL_RenderDrawRect(r, &rect);
      }
    }
  }
  
}

void render_snake(SDL_Renderer* r, std::vector<pair_t> &s, int length){
  SDL_Rect rect;

  rect.w = 13;
  rect.h = 13;

  /* [] operator for vector is constant time complexity */
  for(int i = 0; i < length; i ++){
    rect.x = (s[i].x * 15) + 1;
    rect.y = (s[i].y * 15) + 1;
    
    if(i == 0){
      SDL_SetRenderDrawColor(r, 0, 168, 180, 255);
    }else{
      SDL_SetRenderDrawColor(r, 0, 168, 2, 255);
    }
    SDL_RenderFillRect(r, &rect);
  }

  rect.x = (s[length].x * 15) + 1;
  rect.y = (s[length].y * 15) + 1;

  /* erase last block */
  SDL_SetRenderDrawColor(r, 20, 20, 20, 255);
  SDL_RenderFillRect(r, &rect);

}

void move(std::vector<pair_t> &s, int direction){
  pair_t front = s.front();
  switch(direction){
  case 0: /* up */
    s.insert(s.begin(), {front.x, front.y - 1});
    break;
  case 1: /* right */
    s.insert(s.begin(), {front.x + 1, front.y});
    break;
  case 2: /* down */
    s.insert(s.begin(), {front.x, front.y + 1});
    break;
  case 3: /* left */
    s.insert(s.begin(), {front.x - 1, front.y});
    break;
  }

  s.pop_back();
}

void Engine::init(const char* title, int x_pos, int y_pos, int width,
		  int height, bool fullscreen){
  int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

  snake_length = 3; /* not 4 because last pair is blank */
  snake.push_back({15, 14});
  snake.push_back({14, 14});
  snake.push_back({13, 14});
  snake.push_back({12, 14});/* because last pair in snake is empty */

  direction = 1;
  frame_count = 0;
  
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

  case SDL_KEYDOWN:

    switch(event.key.keysym.sym){
    case 1073741906:
      std::cout << "up" << std::endl;
      if(direction != 2){
	direction = 0;
      }
      break;
    case 1073741903:
      std::cout << "right" << std::endl;
      if(direction != 3){
	direction = 1;
      }
      break;
    case 1073741905:
      std::cout << "down" << std::endl;
      if(direction != 0){
	direction = 2;
      }
      break;
    case 1073741904:
      std::cout << "left" << std::endl;
      if(direction != 1){
	direction = 3;
      }
      break;
    }
    
    break;
  }
}

void Engine::update(){
  if(frame_count > 5){
    move(snake, direction);
    frame_count = 0;
  }

  frame_count++;
}

void Engine::render_screen(){
  SDL_RenderClear(renderer);

  render_walls(renderer);
  render_snake(renderer, snake, snake_length);

  SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
  
  SDL_RenderPresent(renderer);
}

void Engine::terminate(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
