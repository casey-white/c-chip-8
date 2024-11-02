#include <stdio.h>
#include <SDL2/SDL.h>
#include <video.h>
#include <stdbool.h>

int main() {
    printf("TEST");

    if (init_video() < 0) {
        printf("Error occured while initializing the video");
    }

    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    if (cleanup_video() < 0) {
        printf("Error occured while cleaning up the video");
    }

    return 0;
}