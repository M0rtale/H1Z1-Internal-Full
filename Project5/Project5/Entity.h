#pragma once


#include "stdfx.h"
#include "Offsets.h"

namespace Engine
{
	class Entity
	{
	public:
		Vector3& GetPosition();
		Vector3& GetPelvisPos();
		//Vector3& GetNeck();
		//Vector3& GetHead();
		//INT8 GetTeam();
		DWORD& GetHealth();
		DWORD& GetID();
		std::string GetName();
		//Vector4 GetViewAngles();
		//void SetViewAngles(Vector4 vec);
		//void SpottedEsp();
		Vector3& GetHead();
		DWORD GetType();
		Vector3& GetCarPos();
		Vector3& GetItemPos();
		Vector3& GetVelocity();
		float& GetYaw();
		float& GetPitch();
		Vector3 GetHeadFixed();
		int& GetStance();
		std::vector<Vector3> GetBones();
		float& Speed();
	};
}
