/*
H1Z1 Internal made by: M0rtale
*/

#include "DLLMain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		DisableThreadLibraryCalls(hModule); // PERFOMANCE?

		char Buffer[512];
		sprintf_s(Buffer, "Ready! Press Ins to open Menu!");
		MessageBoxA(0, Buffer, "Hey!", MB_SYSTEMMODAL);

		CreateThread(NULL, NULL, Start::Initialise, NULL, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
		Start::Release();
		break;
	}
	return TRUE;
}

