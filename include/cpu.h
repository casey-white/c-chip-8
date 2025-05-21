#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "stdbool.h"

typedef enum {
    ACTION_NEXT,
    ACTION_SKIP,
    ACTION_STEP_BACK,
    ACTION_JUMP
} PCActionsType;

typedef struct {
    PCActionsType action_type;
    unsigned short jump_address;
} PCAction;

typedef struct {
    unsigned short program_counter;
    unsigned char general_registers[16];
    bool* keypad;
    bool video_changed;
    unsigned short stack[16];
    unsigned short index_register;
    unsigned char sound_timer;
    unsigned char delay_timer;
    unsigned char stack_pointer;
    Memory memory;
} CPU;

CPU init_cpu(bool* keypad);

PCAction create_next_action();
PCAction create_skip_action();
PCAction create_step_back_action();
PCAction create_jump_action(unsigned short address);

PCAction clear(Memory *mem);
PCAction ret(CPU *cpu);
PCAction jump(unsigned short address);
PCAction call(CPU *cpu, unsigned short address);
PCAction skip_equal(CPU *cpu, unsigned char target_register, unsigned short kk);
PCAction skip_not_equal(CPU* cpu, unsigned char target_register, unsigned short kk);
PCAction skip_if_registers_equal(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction load_register(CPU *cpu, unsigned char vx, unsigned short kk);
PCAction add_register(CPU *cpu, unsigned char vx, unsigned short kk);
PCAction load_register_to_register(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction or(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction and(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction xor(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction add_with_carry(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction shift_right(CPU *cpu, unsigned char target_register);
PCAction subtract_with_borrow(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction shift_left(CPU *cpu, unsigned char target_register);
PCAction skip_if_registers_not_equal(CPU *cpu, unsigned char vx, unsigned char vy);
PCAction load_index(CPU *cpu, unsigned short addr);
PCAction jump_to(CPU *cpu, unsigned short to_jump);
PCAction random_byte(CPU *cpu, unsigned char vx, unsigned char data);
PCAction display(CPU *cpu, unsigned char vx, unsigned char vy, unsigned char data);
PCAction skip_if_key_press(CPU *cpu, unsigned char vx);
PCAction skip_if_key_not_press(CPU *cpu, unsigned char vx);
PCAction load_delay_timer(CPU *cpu, unsigned char vx);
PCAction load_sound_timer(CPU *cpu, unsigned char vx);
PCAction add_to_index(CPU *cpu, unsigned char vx);
PCAction load_sprite(CPU *cpu, unsigned char vx);
PCAction load_bcd(CPU *cpu, unsigned char vx);
PCAction store_registers(CPU *cpu, unsigned char vx);

#endif