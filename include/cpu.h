#ifndef CPU_H
#define CPU_H

typedef enum {
    ACTION_NEXT,
    ACTION_SKIP,
    ACTION_STEP_BACK,
    ACTION_JUMP
} PCActionsType;

typedef struct {
    PCActionsType action_type;
    unsigned char jump_address;
} PCActions;

#endif