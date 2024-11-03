#ifndef MEMORY_H
#define MEMORY_H

#include <string.h>

int init_memory(void);
int read_at(short address);
int write_at(short address, unsigned char to_write);
int cleanup_memory(void);

#endif