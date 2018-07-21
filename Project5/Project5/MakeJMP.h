// pAddress = address where we want to place our hook
// dwJumpTo = address where we want to jump to
// dwLen    = length of the bytes to overwrite

#include "stdfx.h"

//void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
//{
//	DWORD dwOldProtect, dwBkup, dwRelAddr;
//
//	// give the paged memory read/write permissions
//
//	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
//
//	// calculate the distance between our address and our target location
//	// and subtract the 5bytes, which is the size of the jmp
//	// (0xE9 0xAA 0xBB 0xCC 0xDD) = 5 bytes
//
//	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
//
//	// overwrite the byte at pAddress with the jmp opcode (0xE9)
//
//	*pAddress = 0xE9;
//
//	// overwrite the next 4 bytes (which is the size of a DWORD)
//	// with the dwRelAddr
//
//	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
//
//	// overwrite the remaining bytes with the NOP opcode (0x90)
//	// NOP opcode = No OPeration
//
//	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
//
//	// restore the paged memory permissions saved in dwOldProtect
//
//	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
//
//	return;
//
//}

void MakeNOP(BYTE *pAddress, DWORD dwLen)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	// give the paged memory read/write permissions

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (DWORD x = 0x0; x < dwLen; x++)
	{
		if(*(pAddress + x) != 0x90) // prevent duplicates
			*(pAddress + x) = 0x90;
	}

	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

	return;

}

void MakeRestore(BYTE *pAddress, DWORD dwLen, BYTE* sequence)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (DWORD x = 0x0, i = 0; x < dwLen; x++, i++) *(pAddress + x) = sequence[i];

	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

	return;
}