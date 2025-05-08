#ifndef CRACKING_HPP
#define CRACKING_HPP

#include <string.h>
#include <windows.h>
#include <cstring>
#include <cstdint>

int cracking_nop(int from, int to);
void cracking_hook_function(int from, int to);
void cracking_hook_call(int from, int to);
int cracking_write_hex(int address, char *hex);
void cracking_hook_jmp(unsigned int off, unsigned int loc);

int singleHexToNumber(char hexchar);
int hexToBuffer(char *hex, char *buffer, int bufferLen);

class cHook {
    public:
        uintptr_t from;
        uintptr_t to;
        unsigned char oldCode[5];
    
        void hook_jmp(uintptr_t from, uintptr_t to);
    
        cHook(uintptr_t from, uintptr_t to);
        void hook();
        void unhook();
};
    

#endif