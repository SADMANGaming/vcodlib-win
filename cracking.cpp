#include "cracking.hpp"
#include "windows.h"



int cracking_nop(int from, int to) {
	int ovr = to - from;
	DWORD tmp;
	VirtualProtect((void*)from, ovr, PAGE_EXECUTE_READWRITE, &tmp);
	int i;
	for (i = from; i<to; i++)
	{
		*(unsigned char *)i = 0x90;
		//printf("%d ", *(unsigned char *)i);
	}
	VirtualProtect((void*)from, 5, tmp, &tmp);
	return ovr; // bytes overwritten
}

void cracking_hook_function(int from, int to) {
	DWORD tmp;
	VirtualProtect((void*)from, 5, PAGE_EXECUTE_READWRITE, &tmp);
	int relative = to - (from + 5); // +5 is the position of next opcode
	memset((void *)from, 0xE9, 1); // JMP-OPCODE
	memcpy((void *)(from + 1), &relative, 4); // set relative address with endian
	VirtualProtect((void*)from, 5, tmp, &tmp);
}

void cracking_hook_call(int from, int to)
{
	DWORD tmp;
	VirtualProtect((void*)from, 5, PAGE_EXECUTE_READWRITE, &tmp);
	int relative = to - (from + 5); // +5 is the position of next opcode
	memcpy((void *)(from + 1), &relative, 4); // set relative address with endian
	VirtualProtect((void*)from, 5, tmp, &tmp);
}

void cracking_hook_jmp(unsigned int off, unsigned int loc)
{
	DWORD tmp;
	VirtualProtect((void*)off, 5, PAGE_EXECUTE_READWRITE, &tmp);
	* (unsigned char*)off = 0xe9;
	int foffset = loc - (off + 5);
	memcpy((void*)(off + 1), &foffset, 4);
	FlushInstructionCache(GetCurrentProcess(), (void*)off, 5);
	VirtualProtect((void*)off, 5, tmp, &tmp);
}

int singleHexToNumber(char hexchar)
{
	switch (hexchar)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'a':
	case 'A': return 10;
	case 'b':
	case 'B': return 11;
	case 'c':
	case 'C': return 12;
	case 'd':
	case 'D': return 13;
	case 'e':
	case 'E': return 14;
	case 'f':
	case 'F': return 15;
	}
	return -1;
}
int hexToBuffer(char *hex, char *buffer, int bufferLen)
{
	int len, neededBytes, i, padding, first, pos, leftPart, rightPart;
	len = strlen(hex); // every byte of hex is taking 4 bits. F=1111
	padding = 0; // just for "a", "abc" etc... "a" = 0x0a, "abc" = 0x0abc
	// we dont handle 4-bits for one hex-number, so round up to bytes...
	// three bytes will not take 12 bits, they will use 16 bits = 2 bytes
	if (len % 2 != 0)
	{
		padding = 1;
		len++;
	}
	neededBytes = len >> 1; // its like dividing by 2
	//printf_hide("len=%d neededBytes=%d\n", len, neededBytes);
	first = 1;
	pos = 0;
	for (i = 0; i<neededBytes; i++)
	{
		char twochars[2] = { '0', '0' };
		if (first)
		{
			if (padding) {
				twochars[1] = hex[0];
				pos++;
			}
			else {
				twochars[0] = hex[0];
				twochars[1] = hex[1];
				pos += 2;
			}
			first = 0;
		}
		else {
			twochars[0] = hex[pos];
			twochars[1] = hex[pos + 1];
			pos += 2;
		}
		//printf_hide("twochars=%.2s\n", twochars);
		leftPart = singleHexToNumber(twochars[0]);
		rightPart = singleHexToNumber(twochars[1]);
		if (leftPart == -1 || rightPart == -1)
			return i;
		buffer[i] = (leftPart << 4) + rightPart;
		// buffer end:
		if (i == bufferLen)
			return i;
	}
	return neededBytes;
}



int cracking_write_hex(int address, char *hex)
{
	unsigned char *ptr = (unsigned char *)address;
	char buffer[128] = { 0 };
	int bytes;
	int i;
	bytes = hexToBuffer(hex, buffer, 128);


	for (i = 0; i<bytes; i++)
		ptr[i] = buffer[i];

	return bytes;
}
cHook::cHook(uintptr_t from, uintptr_t to) {
    this->from = from;
    this->to = to;
}

void cHook::hook_jmp(uintptr_t from, uintptr_t to) {
    DWORD oldProtect;
    VirtualProtect((void*)from, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

    *(BYTE*)from = 0xE9; // JMP opcode
    *(uintptr_t*)(from + 1) = to - from - 5;

    VirtualProtect((void*)from, 5, oldProtect, &oldProtect);
}

void cHook::hook() {
    DWORD oldProtect;
    VirtualProtect((void*)from, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

    memcpy(oldCode, (void*)from, 5); // Save original bytes
    hook_jmp(from, to);

    VirtualProtect((void*)from, 5, oldProtect, &oldProtect);
}

void cHook::unhook() {
    DWORD oldProtect;
    VirtualProtect((void*)from, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

    memcpy((void*)from, oldCode, 5); // Restore original bytes

    VirtualProtect((void*)from, 5, oldProtect, &oldProtect);
}