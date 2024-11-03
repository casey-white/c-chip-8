#include <stdio.h>
#include "cpu.h"

PCActions create_next_action() {
    return (PCActions){.action_type = ACTION_NEXT};
}

PCActions create_skip_action() {
    return (PCActions){.action_type = ACTION_SKIP};
}

PCActions create_step_back_action() {
    return (PCActions){.action_type = ACTION_STEP_BACK};
}

PCActions create_jump_action(short address) {
    return (PCActions){.action_type = ACTION_JUMP, .jump_address = address};
}
