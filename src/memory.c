#include "memory.h"

Memory init_memory() {

    Memory mem;

    memset(mem.memory, 0, 4096 * sizeof(unsigned char));
    memset(mem.video_buffer, 0, sizeof(bool) * (32 * 64));

    return mem; 
}

int read_at(Memory *mem, short address) {
    if (address < 0 || address > MEMORY_SIZE) return -1;
    return mem->memory[address];
}

int write_at(Memory *mem, short address, unsigned char to_write) {
    if (address < 0 || address > MEMORY_SIZE) return -1;

    mem->memory[address] = to_write;

    return 0;
}

int clear_video_buffer(Memory *mem) {
    memset(mem->video_buffer, 0, sizeof(bool) * (32 * 64));

    return 0;
}

int clear_memory(Memory *mem) {
    memset(mem->memory, 0, 4096 * sizeof(unsigned char));

    return 0;
}