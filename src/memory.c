

#define MEMORY_SIZE 4096
#define MEM_START 0x200

static unsigned char memory[MEMORY_SIZE];

int init_memory() {
   memset(&memory, 0, 4096 * sizeof(unsigned char));

   return 0; 
}

int read_at(short address) {
    if (address < 0 || address > MEMORY_SIZE) return -1;
    return memory[address];
}

int write_at(short address, unsigned char to_write) {
    if (address < 0 || address > MEMORY_SIZE) return -1;

    memory[address] = to_write;

    return 0;
}

int clear_memory() {
    memset(&memory, 0, 4096 * sizeof(unsigned char));
}