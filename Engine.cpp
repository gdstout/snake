#include "Engine.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

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

void render_apple(SDL_Renderer *r, pair_t &a){
  SDL_Rect rect;

  rect.w = 13;
  rect.h = 13;
  rect.x = (a.x * 15) + 1;
  rect.y = (a.y * 15) + 1;
  
  SDL_SetRenderDrawColor(r, 232, 55, 55, 255);
  SDL_RenderFillRect(r, &rect);
}

bool collision_with_snake(pair_t pair, std::vector<pair_t> &s){
  for(auto &i : s){
    if(i.x == pair.x && i.y == pair.y){
      return true;
    }
  }
  return false;
}

void Engine::new_apple_position(){
  do{
    /* in between 1 and 28 */
    apple.x = rand() % 27 + 1;
    apple.y = rand() % 27 + 1;
  }while(collision_with_snake(apple, snake));
}


void Engine::move(){
  pair_t front = snake.front();
  pair_t new_front;
  switch(direction){
  case 0: /* up */
    new_front.x = front.x;
    new_front.y = front.y - 1;
    break;
  case 1: /* right */
    new_front.x = front.x + 1;
    new_front.y = front.y;
    break;
  case 2: /* down */
    new_front.x = front.x;
    new_front.y = front.y + 1;
    break;
  case 3: /* left */
    new_front.x = front.x - 1;
    new_front.y = front.y;
    break;
  }

  /* check to see if new front location is invalid */
  if(new_front.x == 0 || new_front.y == 0 || new_front.x == 29 ||
     new_front.y == 29){
    terminate();
  }
  if(collision_with_snake(new_front, snake)){
    terminate();
  }

  /* check to see if new front location is apple */
  if(new_front.x == apple.x && new_front.y == apple.y){
    new_apple_position();
    snake_length ++;
    snake.push_back(snake.back());
  }

  snake.insert(snake.begin(), new_front);

  snake.pop_back();
}

void Engine::init(const char* title, int x_pos, int y_pos, int width,
		  int height, bool fullscreen){
  int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

  srand(time(NULL));

  snake_length = 3; /* not 4 because last pair is blank */
  snake.push_back({15, 14});
  snake.push_back({14, 14});
  snake.push_back({13, 14});
  snake.push_back({12, 14});/* because last pair in snake is empty */

  new_apple_position();

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
  if(frame_count > 7){
    move();
    frame_count = 0;
  }

  frame_count++;
}

void Engine::render_screen(){
  SDL_RenderClear(renderer);

  render_walls(renderer);
  render_snake(renderer, snake, snake_length);
  render_apple(renderer, apple);

  SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
  
  SDL_RenderPresent(renderer);
}

void Engine::terminate(){
  is_running = false;
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
