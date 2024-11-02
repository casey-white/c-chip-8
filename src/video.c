#include <stdio.h>
#include <SDL2/SDL.h>

#define VIDEO_HEIGHT 320
#define VIDEO_WIDTH 640
#define BACKGROUND_COLOR 0xFF000000  // Black (opaque)
#define TARGET_COLOR 0xFF00FF00  // Green

static SDL_Window* window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture* texture = NULL;

int init_video() {
    short error_code = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL couldn't be initialized! SDL_ERROR: %s\n", SDL_GetError());
        error_code = -1;
        return error_code;
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VIDEO_WIDTH, VIDEO_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, VIDEO_WIDTH, VIDEO_HEIGHT);

    return error_code;
}

int render_frame(u_int8_t *video_buffer) {

    u_int32_t color_buffer[VIDEO_WIDTH * VIDEO_HEIGHT];
    for (int i = 0; i < VIDEO_WIDTH * VIDEO_HEIGHT; ++i) {
        color_buffer[i] = video_buffer[i] ? TARGET_COLOR : BACKGROUND_COLOR;
    }

    SDL_UpdateTexture(texture, NULL, color_buffer, VIDEO_WIDTH * VIDEO_HEIGHT);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    return 0;
}

int cleanup_video() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_Quit();

    return 0;
}