#include <stdio.h>
#include "memory.h"
#include "cpu.h"

PCAction create_next_action() {
    return (PCAction){.action_type = ACTION_NEXT};
}

PCAction create_skip_action() {
    return (PCAction){.action_type = ACTION_SKIP};
}

PCAction create_step_back_action() {
    return (PCAction){.action_type = ACTION_STEP_BACK};
}

PCAction create_jump_action(short address) {
    return (PCAction){.action_type = ACTION_JUMP, .jump_address = address};
}

static short program_counter;
static short general_registers[16];
static short stack[16];
static short index_register;
static unsigned char sound_timer;
static unsigned char delay_timer;
static unsigned char stack_pointer;

int init_cpu() {

    program_counter = 0x200;
    memset(&general_registers, 0, 16 * sizeof(short));
    memset(&stack, 0, 16 * sizeof(short));
    index_register = 0;
    sound_timer = 0;
    delay_timer = 0;
    stack_pointer = 0;

    return 0;
}


PCAction clear() {
    clear_video_buffer();
    return create_next_action();
}

PCAction ret() {
    short address = stack[stack_pointer];
    stack_pointer -= 1;
    return create_jump_action(address);
}

PCAction jump(short address) {
    return create_jump_action(address);
}

PCAction call(short address) {
    stack_pointer += 1;
    stack[stack_pointer] = address;
    return create_jump_action(address);
}

PCAction skip_equal(unsigned char target_register, unsigned char value) {
    if (target_register == value) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction skip_not_equal(unsigned char target_register, unsigned char value) {
    if (target_register != value) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction skip_if_registers_equal(unsigned char vx, unsigned char vy) {
    if (general_registers[vx] == general_registers[vy]) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction skip_if_registers_not_equal(unsigned char vx, unsigned char vy) {
    if (general_registers[vx] != general_registers[vy]) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction load_register(unsigned char vx, short kk) {
    general_registers[vx] != kk;
    return create_next_action();
}

PCAction add_register(unsigned char vx, short kk) {
    general_registers[vx] += kk;
    return create_next_action();
}

PCAction load_register_to_register(unsigned char vx, unsigned char vy) {
    general_registers[vx] = general_registers[vy];
    return create_next_action();
}

PCAction or(unsigned char vx, unsigned char vy) {
    general_registers[vx] = general_registers[vx] | general_registers[vy];
    return create_next_action();
}

PCAction and(unsigned char vx, unsigned char vy) {
    general_registers[vx] = general_registers[vx] & general_registers[vy];
    return create_next_action();
}

PCAction xor(unsigned char vx, unsigned char vy) {
    general_registers[vx] = general_registers[vx] ^ general_registers[vy];
    return create_next_action();
}

PCAction add_with_carry(unsigned char vx, unsigned char vy) {
    if ((general_registers[vx] + general_registers[vy]) > 0xFF) {
        general_registers[0xF] = 1;
    }
    return create_next_action();
}