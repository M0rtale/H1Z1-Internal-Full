/**
* H1Z1 SDK
* Made by M0rtale
*/

#include <windows.h>

#include "Offsets.h"
#include "Memory.h"
#include "Helpers.h"
#include "CGame.h"

namespace Engine
{
	CGame* CGame::GetInstance()
	{
		return *reinterpret_cast<CGame**>(ADDRESS_CGAME /*+ reinterpret_cast<uint64_t>(GetModuleHandle(NULL))*/);
	}

	Entity* CGame::GetLocalPlayer()
	{
		return *Memory::Ptr<Entity**>(this, OFFSET_LocalPlayer);
	}

	std::vector<Entity*> CGame::GetPlayers()
	{
		std::vector<Entity*> Lists = {};

		INT8 Count = *Memory::Ptr<INT8*>(this, OFFSET_EntityCount);

		//Helpers::Log(XorStr("Count"));

		auto Ent = *Memory::Ptr<Entity**>(this, OFFSET_LocalPlayer);

		//Helpers::Log(XorStr("Local"));

		//for (int i = 0; i < Count && Ent != nullptr && Ent; i++)
		for(;;)
		{
			if (Ent == nullptr && !Ent)
				break;

			Ent = *Memory::Ptr<Entity**>(Ent, OFFSET_NEXTPLAYER);

			//Helpers::LogInt(XorStr("Number "), i);

			Lists.push_back(Ent);
		}

		return Lists;
	}

	std::vector<Entity*> CGame::GetObjects()
	{
		std::vector<Entity*> Lists = {};

		INT8 Count = *Memory::Ptr<INT8*>(this, OFFSET_EntityCount);

		//Helpers::Log(XorStr("Count"));

		auto Ent = *Memory::Ptr<Entity**>(this, OFFSET_LocalPlayer);

		//Helpers::Log(XorStr("Local"));

		//for (int i = 0; i < Count && Ent != nullptr && Ent; i++)
		for (;;)
		{
			if (Ent == nullptr && !Ent)
				break;

			Ent = *Memory::Ptr<Entity**>(Ent, OFFSET_NEXTOBJECT);

			//Helpers::LogInt(XorStr("Number "), i);

			Lists.push_back(Ent);
		}

		return Lists;
	}
}