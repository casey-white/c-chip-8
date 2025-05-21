#include <stdio.h>
#include <SDL2/SDL.h>

#include "keypad.h"

int init_events(void) {
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
        return -1;
    } 

    return 0;
}

int poll_keys(SDL_Event* e, bool* keys) {
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) return -1;
        if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return -1;
            case SDLK_1:
                keys[0] = true;
                break;
            case SDLK_2:
                keys[1] = true;
                break;
            case SDLK_3:
                keys[2] = true;
                break;
            case SDLK_4:
                keys[3] = true;
                break;
            case SDLK_q:
                keys[4] = true;
                break;
            case SDLK_w:
                keys[5] = true;
                break;
            case SDLK_e:
                keys[6] = true;
                break;
            case SDLK_r:
                keys[7] = true;
                break;
            case SDLK_a:
                keys[8] = true;
                break;
            case SDLK_s:
                keys[9] = true;
                break;
            case SDLK_d:
                keys[10] = true;
                break;
            case SDLK_f:
                keys[11] = true;
                break;
            case SDLK_z:
                keys[12] = true;
                break;
            case SDLK_x:
                keys[13] = true;
                break;
            case SDLK_c:
                keys[14] = true;
                break;
            case SDLK_v:
                keys[15] = true;
                break;
            
            default:
                break;
            }
        }
        if (e->type == SDL_KEYUP) {
            switch (e->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return -1;
            case SDLK_1:
                keys[0] = false;
                break;
            case SDLK_2:
                keys[1] = false;
                break;
            case SDLK_3:
                keys[2] = false;
                break;
            case SDLK_4:
                keys[3] = false;
                break;
            case SDLK_q:
                keys[4] = false;
                break;
            case SDLK_w:
                keys[5] = false;
                break;
            case SDLK_e:
                keys[6] = false;
                break;
            case SDLK_r:
                keys[7] = false;
                break;
            case SDLK_a:
                keys[8] = false;
                break;
            case SDLK_s:
                keys[9] = false;
                break;
            case SDLK_d:
                keys[10] = false;
                break;
            case SDLK_f:
                keys[11] = false;
                break;
            case SDLK_z:
                keys[12] = false;
                break;
            case SDLK_x:
                keys[13] = false;
                break;
            case SDLK_c:
                keys[14] = false;
                break;
            case SDLK_v:
                keys[15] = false;
                break;
            
            default:
                break;
            }
        }

    }

    return 0;
}