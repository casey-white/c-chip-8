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
    short jump_address;
} PCAction;

PCAction create_next_action();
PCAction create_skip_action();
PCAction create_step_back_action();
PCAction create_jump_action(short address);

PCAction clear();


#endif