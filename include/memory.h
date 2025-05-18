#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define MEM_START 0x200

typedef struct {
    unsigned char memory[MEMORY_SIZE];
    bool video_buffer[32 * 64];    
} Memory;

Memory init_memory(void);
int read_at(Memory *mem, short address);
int write_at(Memory *mem, short address, unsigned char to_write);
int clear_video_buffer(Memory *mem);
int clear_memory(Memory *mem);

#endif