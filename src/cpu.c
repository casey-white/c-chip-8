#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cpu.h"
#include "memory.h"

PCAction create_next_action() {
    return (PCAction){.action_type = ACTION_NEXT};
}

PCAction create_skip_action() {
    return (PCAction){.action_type = ACTION_SKIP};
}

PCAction create_step_back_action() {
    return (PCAction){.action_type = ACTION_STEP_BACK};
}

PCAction create_jump_action(unsigned short address) {
    return (PCAction){.action_type = ACTION_JUMP, .jump_address = address};
}

CPU init_cpu(bool* keypad) {

    CPU cpu;

    memset(cpu.general_registers, 0, 16 * sizeof(short));
    memset(cpu.stack, 0, 16 * sizeof(short));
    cpu.program_counter = 0x200;
    cpu.keypad = keypad;
    cpu.video_changed = 0;
    cpu.index_register = 0;
    cpu.delay_timer = 0;
    cpu.sound_timer = 0;
    cpu.stack_pointer = 0;
    cpu.memory = init_memory();

    return cpu;
}


PCAction clear(Memory *mem) {
    clear_video_buffer(mem);
    return create_next_action();
}

PCAction ret(CPU *cpu) {
    unsigned short address = cpu->stack[cpu->stack_pointer];
    cpu->stack_pointer -= 1;
    return create_jump_action(address);
}

PCAction jump(unsigned short address) {
    return create_jump_action(address);
}

PCAction call(CPU *cpu, unsigned short address) {
    cpu->stack[cpu->stack_pointer] = address;
    cpu->stack_pointer += 1;
    return create_jump_action(address);
}

PCAction skip_equal(CPU *cpu, unsigned char target_register, unsigned short kk) {
    if (cpu->general_registers[target_register] == kk) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction skip_not_equal(CPU *cpu, unsigned char target_register, unsigned short kk) {
    if (cpu->general_registers[target_register] != kk) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction skip_if_registers_equal(CPU *cpu, unsigned char vx, unsigned char vy) {
    if (cpu->general_registers[vx] == cpu->general_registers[vy]) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction load_register(CPU *cpu, unsigned char vx, unsigned short kk) {
    cpu->general_registers[vx] = kk;
    return create_next_action();
}

PCAction add_register(CPU *cpu, unsigned char vx, unsigned short kk) {
    cpu->general_registers[vx] += kk;
    return create_next_action();
}

PCAction load_register_to_register(CPU *cpu, unsigned char vx, unsigned char vy) {
    cpu->general_registers[vx] = cpu->general_registers[vy];
    return create_next_action();
}

PCAction or(CPU *cpu, unsigned char vx, unsigned char vy) {
    cpu->general_registers[vx] = cpu->general_registers[vx] | cpu->general_registers[vy];
    return create_next_action();
}

PCAction and(CPU *cpu, unsigned char vx, unsigned char vy) {
    cpu->general_registers[vx] = cpu->general_registers[vx] & cpu->general_registers[vy];
    return create_next_action();
}

PCAction xor(CPU *cpu, unsigned char vx, unsigned char vy) {
    cpu->general_registers[vx] = cpu->general_registers[vx] ^ cpu->general_registers[vy];
    return create_next_action();
}

PCAction add_with_carry(CPU *cpu, unsigned char vx, unsigned char vy) {
    if ((cpu->general_registers[vx] + cpu->general_registers[vy]) > 0xFF) {
        cpu->general_registers[0xF] = 1;
    }
    cpu->general_registers[vx] = cpu->general_registers[vx] + cpu->general_registers[vy];
    return create_next_action();
}

PCAction subtract_with_borrow(CPU *cpu, unsigned char vx, unsigned char vy) {
    if (cpu->general_registers[vy] > cpu->general_registers[vx]) {
        cpu->general_registers[0xF] = 1;
    }
    cpu->general_registers[vx] = cpu->general_registers[vy] - cpu->general_registers[vx];
    return create_next_action();
}

PCAction shift_right(CPU *cpu, unsigned char target_register) {
    if (cpu->general_registers[target_register] & 1) {
        cpu->general_registers[0xF] = 1;
    }
    cpu->general_registers[target_register] = cpu->general_registers[target_register] >> 1;
    return create_next_action();
}

PCAction shift_left(CPU *cpu, unsigned char target_register) {
    if (cpu->general_registers[target_register] & (1 << 7)) {
        cpu->general_registers[0xF] = 1;
    }
    cpu->general_registers[target_register] = cpu->general_registers[target_register] * 2;
    return create_next_action();
}

PCAction skip_if_registers_not_equal(CPU *cpu, unsigned char vx, unsigned char vy) {
    if (cpu->general_registers[vx] != cpu->general_registers[vy]) {
        return create_skip_action();
    }
    return create_next_action();
}

PCAction load_index(CPU *cpu, unsigned short addr) {
    cpu->index_register = addr;
    return create_next_action();
}

PCAction jump_to(CPU *cpu, unsigned short addr) {
    return create_jump_action(addr + cpu->general_registers[0x0]);
}

PCAction random_byte(CPU *cpu, unsigned char vx, unsigned char kk) {
    srand(time(NULL));
    unsigned char r = rand() % 255;
    cpu->general_registers[vx] = r & kk;
    return create_next_action();
}

PCAction display(CPU *cpu, unsigned char vx, unsigned char vy, unsigned char data) {
    unsigned short index = cpu->index_register;

    cpu->general_registers[0x0F] = 0;

    for(int row = 0; row < data; row++) {
        unsigned char y = (cpu->general_registers[vx] + row) % 32;
        unsigned short current_byte = read_at(&cpu->memory, index + row);
        for(int col = 0; col < 8; col++) {
            unsigned char x = (cpu->general_registers[vy] + col) % 64;
            bool bit_on = (current_byte >> (7 - col)) & 1;

            cpu->general_registers[0x0F] |= bit_on & cpu->memory.video_buffer[x + (64 * y)];
            cpu->memory.video_buffer[x + (y * 64)] = bit_on;       
        }
    }

    cpu->video_changed = 1;
    return create_next_action();
   
}

PCAction skip_if_key_press(CPU *cpu, unsigned char vx) {
    if (cpu->keypad[cpu->general_registers[vx]]) {
        return create_skip_action();
    } else {
        return create_next_action();
    }
}

PCAction skip_if_key_not_press(CPU *cpu, unsigned char vx) {
    if (!cpu->keypad[cpu->general_registers[vx]]) {
        return create_skip_action();
    } else {
        return create_next_action();
    }
}

PCAction load_delay_timer(CPU *cpu, unsigned char vx) {
    cpu->delay_timer = cpu->general_registers[vx];
    return create_next_action();
}

PCAction load_sound_timer(CPU *cpu, unsigned char vx) {
    cpu->sound_timer = cpu->general_registers[vx];
    return create_next_action();
}

PCAction add_to_index(CPU *cpu, unsigned char vx) {
    cpu->index_register = cpu->index_register + cpu->general_registers[vx];
    return create_next_action();
}

PCAction load_sprite(CPU *cpu, unsigned char vx) {
    int offset = 0x50;
    cpu->index_register = offset + (5 * cpu->general_registers[vx]);
    return create_next_action();
}

PCAction load_bcd(CPU *cpu, unsigned char vx) {
    unsigned char register_value = cpu->general_registers[vx];
    unsigned short index_address = cpu->index_register;

    unsigned char hundred = (register_value / 100);
    unsigned char ten = (register_value % 100) / 10;
    unsigned char one = register_value % 10;

    write_at(&cpu->memory, index_address, hundred);
    write_at(&cpu->memory, index_address + 1, ten);
    write_at(&cpu->memory, index_address + 2, one);

    return create_next_action();
}

PCAction store_registers(CPU *cpu, unsigned char vx) {

    for (int i = 0; i <= vx; i++) {
        write_at(&cpu->memory, cpu->index_register + i, cpu->general_registers[i]);
    }
    return create_next_action();
}

PCAction load_registers(CPU *cpu, unsigned char vx) {
    for (int i = 0; i <= vx; i++) {
        cpu->general_registers[i] = read_at(&cpu->memory, cpu->index_register + i);
    }
    return create_next_action();
}
