#include "mem.h"

BYTE Buff[100];

//Stolen from Starcraft hacks
//These will just set the page to read/write/execute and will help us add Calls and Jumps.
void MemPatch(BYTE* Dest, BYTE* Src, int Len) {
	DWORD Old;

	VirtualProtect(Dest, Len, PAGE_EXECUTE_READWRITE, &Old);
	memcpy(Dest, Src, Len);
	VirtualProtect(Dest, Len, Old, &Old);
}

void MemPatchInt(BYTE* Dest, unsigned int* Src, int Len) {
	DWORD Old;

	VirtualProtect(Dest, Len, PAGE_EXECUTE_READWRITE, &Old);
	memcpy(Dest, Src, Len);
	VirtualProtect(Dest, Len, Old, &Old);
}

void CallPatch(BYTE* Dest, BYTE* Src, int Nops) {
	Buff[0] = 0xE8;
	*(int*)&Buff[1] = Src - (Dest + 5);

	for (int i = 5; i < Nops + 5; i++) {
		Buff[i] = 0x90;
	}
	MemPatch(Dest, Buff, Nops + 5);
}

void JumpPatch(BYTE* Dest, BYTE* Src, int Nops) {
	Buff[0] = 0xE9;
	*(int*)&Buff[1] = Src - (Dest + 5);

	for (int i = 5; i < Nops + 5; i++) {
		Buff[i] = 0x90;
	}
	MemPatch(Dest, Buff, Nops + 5);
}

template<typename T>
void MemPatchTemplate(BYTE* Dest, T Src, int Len) {
	DWORD Old;

	VirtualProtect(Dest, Len, PAGE_EXECUTE_READWRITE, &Old);
	memcpy(Dest, Src, Len);
	VirtualProtect(Dest, Len, Old, &Old);
}

template<class T>
void GetFuncAddr(void *func) {

	std::function<void(T*)> memfun(&T::func);
	
}
