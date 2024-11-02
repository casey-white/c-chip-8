#include <stdio.h>
#include <SDL2/SDL.h>
#include <video.h>
#include <stdbool.h>

int main() {
    printf("TEST");

    if (init_video() < 0) {
        printf("Error occured while initializing the video");
    }

    u_int8_t temp_buffer[64 * 32];

    memset(&temp_buffer, 0, sizeof(temp_buffer));


    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        render_frame(temp_buffer);
    }

    if (cleanup_video() < 0) {
        printf("Error occured while cleaning up the video");
    }

    return 0;
}