#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdbool.h>

int init_events(void);
int poll_keys(SDL_Event* e, bool* keys);

#endif
