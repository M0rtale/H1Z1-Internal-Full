#pragma once
#include "stdfx.h"

namespace Helpers
{
	void LogAddress(char* szName, int64_t iAddress);
	void LogFloat(char* szName, float fValue);
	void LogError(char* szMessage);
	void Log(char* szMessage);
	void LogChar(char szMessage);
	void LogInt(char* szMessage, int iAdress);
	void LogString(char* szName, std::string sValue);
	void HookFunction(PVOID *oFunction, PVOID pDetour);
	void UnhookFunction(PVOID *oFunction, PVOID pDetour);
	std::string VariableText(const char* format, ...);

	inline void**& getvtable(void* inst, size_t offset = 0)
	{
		return *reinterpret_cast<void***>((size_t)inst + offset);
	}

	inline const void** getvtable(const void* inst, size_t offset = 0)
	{
		return *reinterpret_cast<const void***>((size_t)inst + offset);
	}

	template< typename Fn >
	inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
	{
		return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
	}

	template< typename T > inline T* makeptr(void* ptr, int offset)
	{
		return reinterpret_cast<T*>((size_t)ptr + offset);
	}
	template< typename T > inline T* makeptr(DWORD ptr, int offset)
	{
		return reinterpret_cast<T*>((size_t)ptr + offset);
	}
}