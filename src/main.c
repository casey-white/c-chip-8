#include <stdio.h>
#include <SDL2/SDL.h>
#include <video.h>
#include "keypad.h"
#include <stdbool.h>

#define TARGET_FPS 60
#define TARGET_DELAY (1000 / TARGET_FPS)

int main() {

    if (init_video() < 0 || init_events() < 0) {
        printf("Error occured while initializing the video");
    }

    bool* keypad = (bool*)calloc(16, sizeof(bool));

    u_int8_t temp_buffer[64 * 32];

    memset(&temp_buffer, 1, sizeof(temp_buffer));
    int running = 1;
    SDL_Event event;
    u_int32_t frame_start, frame_time;
    while (poll_keys(&event, keypad) >= 0) {
        frame_start = SDL_GetTicks();
        printf("Keypad State:\n");
        printf("%s %s %s %s\n", keypad[0] ? "Pressed" : "Released", keypad[1] ? "Pressed" : "Released", keypad[2] ? "Pressed" : "Released", keypad[3] ? "Pressed" : "Released");
        printf("%s %s %s %s\n", keypad[4] ? "Pressed" : "Released", keypad[5] ? "Pressed" : "Released", keypad[6] ? "Pressed" : "Released", keypad[7] ? "Pressed" : "Released");
        printf("%s %s %s %s\n", keypad[8] ? "Pressed" : "Released", keypad[9] ? "Pressed" : "Released", keypad[10] ? "Pressed" : "Released", keypad[11] ? "Pressed" : "Released");
        printf("%s %s %s %s\n", keypad[12] ? "Pressed" : "Released", keypad[13] ? "Pressed" : "Released", keypad[14] ? "Pressed" : "Released", keypad[15] ? "Pressed" : "Released");      
        render_frame(temp_buffer);
        frame_time  = SDL_GetTicks() - frame_start;

        if (frame_time < TARGET_DELAY) {
            SDL_Delay(TARGET_DELAY - frame_time);
        }
    }

    if (cleanup_video() < 0) {
        printf("Error occured while cleaning up the video");
    }

    free(keypad);

    return 0;
}