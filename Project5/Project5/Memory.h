/**
 * Rainbow Six: Siege SDK
 * Copyright (C) 2017 RangeMachine
 */

#pragma once

#include <cstdint>
#include <type_traits>
	
namespace Engine
{
	class Memory
	{
		public:
			template <typename Type, typename Base, typename Offset>
			static inline Type Ptr(Base base, Offset offset)
			{

				return base ? reinterpret_cast<Type>((reinterpret_cast<uint64_t>(base) + static_cast<uint64_t>(offset))) : nullptr;
			}

			template <typename Type>
			static bool IsValidPtr(Type* ptr)
			{
				return (ptr && sizeof(ptr)) ? true : false;
			}

			static bool IsValidPtr(DWORD* ptr)
			{
				return (ptr && sizeof(ptr)) ? true : false;
			}
	};
}