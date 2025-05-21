#include <SDL2/SDL.h>
#include "unity.h"
#include "keypad.h"

void setUp(void) {
    SDL_Init(SDL_INIT_EVENTS);
}

void tearDown(void) {
    SDL_Quit();
}

void test_poll_quit() {
    SDL_Event event;
    bool* keypad = (bool*)malloc(16 * sizeof(bool));

    SDL_Event quit_event;
    quit_event.type = SDL_QUIT;
    SDL_PushEvent(&quit_event);

    int status_code = poll_keys(&event, keypad);

    TEST_ASSERT_EQUAL(-1, status_code);

    free(keypad);
}

void test_poll_keydown() {
    SDL_Event event;
    bool* keypad = (bool*)malloc(16 * sizeof(bool));

    SDL_Event escape_event;
    escape_event.type = SDL_KEYDOWN;
    escape_event.key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent(&escape_event);

    int status_code = poll_keys(&event, keypad);

    TEST_ASSERT_EQUAL(-1, status_code);

    free(keypad);
}

void test_poll_keydown_and_keyup() {
    SDL_Event event;
    bool* keypad = (bool*)malloc(16 * sizeof(bool));

    SDL_Event keydown_event;
    keydown_event.type = SDL_KEYDOWN;
    keydown_event.key.keysym.sym = SDLK_1;
    SDL_PushEvent(&keydown_event);

    int status_code = poll_keys(&event, keypad);

    TEST_ASSERT_EQUAL(0, status_code);
    TEST_ASSERT_EQUAL(1, keypad[0]);

    SDL_Event keyup_event;
    keyup_event.type = SDL_KEYUP;
    keyup_event.key.keysym.sym = SDLK_1;
    SDL_PushEvent(&keyup_event);

    status_code = poll_keys(&event, keypad);


    TEST_ASSERT_EQUAL(0, status_code);
    TEST_ASSERT_EQUAL(0, keypad[0]);


    free(keypad);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_poll_quit);
    RUN_TEST(test_poll_keydown);
    RUN_TEST(test_poll_keydown_and_keyup);

    return UNITY_END();
}


