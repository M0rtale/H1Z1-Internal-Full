
#include "Helpers.h"
#include <vector>
#include <Psapi.h>
#include "detours.h"

#define INRANGE(x, a, b)	(x >= a && x <= b)
#define GETBITS(x)			(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE(x)			(GETBITS(x[0]) << 4 | GETBITS(x[1]))

//HOOKING
void Helpers::HookFunction(PVOID *oFunction, PVOID pDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(oFunction, pDetour);
	DetourTransactionCommit();
}
void Helpers::UnhookFunction(PVOID *oFunction, PVOID pDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(oFunction, pDetour);
	DetourTransactionCommit();
}

//MISCELLANEOUS
void Helpers::Log(char* szMessage)
{
	std::cout << "[++] " << szMessage << std::endl;
}
void Helpers::LogChar(char szMessage)
{
	std::cout << "[++] " << szMessage << std::endl;
}
void Helpers::LogInt(char* szMessage, int iAdress)
{
	std::cout << "[++] " << szMessage << ": " << std::defaultfloat << iAdress << std::endl;
}
void Helpers::LogAddress(char* szName, int64_t iAddress)
{
	std::cout << "[++] " << szName << XorStr(": 0x") << std::hex << iAddress << std::endl;
}
void Helpers::LogFloat(char* szName, float fValue)
{
	std::cout << "[++] " << szName << ": " << std::defaultfloat << fValue;
}
void Helpers::LogString(char* szName, std::string sValue)
{
	std::cout << "[++] " << szName << ": " << sValue << std::endl;
}
void Helpers::LogError(char* szMessage)
{
	std::cout << "[Error] " << szMessage << std::endl;
}

// CONVERTERS
std::string Helpers::VariableText(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr);

	va_end(argptr);

	return buffer;
}

// PATTERN SCANNING


