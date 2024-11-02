#include <stdio.h>
#include <SDL2/SDL.h>

static SDL_Window* window = NULL;
static SDL_Renderer *renderer = NULL;

int init_video() {
    short error_code = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL couldn't be initialized! SDL_ERROR: %s\n", SDL_GetError());
        error_code = -1;
        return error_code;
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    return error_code;
}

int cleanup_video() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();

    return 0;
}