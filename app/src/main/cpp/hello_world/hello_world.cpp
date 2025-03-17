#include "hello_world.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

int hello_world() {
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(
    "An SDL2 window",
    360,
    640,
    SDL_WINDOW_OPENGL
  );
  if (window == NULL) {
    SDL_Log("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer* renderer = NULL;
  renderer = SDL_CreateRenderer(window, NULL);
  if( renderer == NULL ) {
    SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    return 1;
  }

  SDL_Surface *loadedImage = IMG_Load("res/hello.png");
  if (loadedImage == NULL) {
    SDL_Log("Could not find file: res/hello.png");
    return 1;
  }

  SDL_Rect r;
  r.x = 50;
  r.y = 50;
  r.w = loadedImage->w;
  r.h = loadedImage->h;

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
  if (texture == NULL) {
    SDL_Log("Could not create texture: %s\n", SDL_GetError());
    return 1;
  }
  SDL_DestroySurface(loadedImage);

  // Main loop flag
  bool quit = false;

  SDL_Event sdlEvent;

  while(!quit) {
    //Handle events on queue
    while(SDL_PollEvent(&sdlEvent) != 0 ) {
      //User requests quit
      if (sdlEvent.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); // Set render color to red ( background will be rendered in this color )
    SDL_RenderClear( renderer ); // Clear window
    SDL_FRect fr = {
        static_cast<float>(r.x),
        static_cast<float>(r.y),
        static_cast<float>(r.w),
        static_cast<float>(r.h)
    };
    SDL_RenderTexture(renderer, texture, NULL, &fr); // Render our image
    SDL_RenderPresent(renderer); // Render the rect to the screen
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
