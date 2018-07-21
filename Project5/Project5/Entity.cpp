#include "Entity.h"


namespace Engine
{
	Vector3& Entity::GetPosition()
	{
		Vector3 Empty = Vector3(0, 0, 0);

		auto base = *Memory::Ptr<DWORD**>(this, OFFSET_PLAYER_BASE);

		if (!base)
			return Empty;

		return *Memory::Ptr<Vector3*>(base, OFFSET_VBASEPOS);
	}

	Vector3& Entity::GetPelvisPos()
	{
		Vector3 Empty = Vector3(0, 0, 0);

		auto base = *Memory::Ptr<DWORD**>(this, OFFSET_PLAYER_BASE);

		if (!base)
			return Empty;

		return *Memory::Ptr<Vector3*>(base, OFFSET_VPELVISPOS);
	}

	DWORD& Entity::GetID()
	{
		return *Memory::Ptr<DWORD*>(this, OFFSET_ID);
	}

	DWORD& Entity::GetHealth()
	{
		DWORD Empty = 0;

		auto base = *Memory::Ptr<DWORD**>(this, OFFSET_HEALTHBASE);

		if (!base)
			return Empty;

		DWORD& health = *Memory::Ptr<DWORD*>(base, OFFSET_HEALTH);

		if (!base)
			return Empty;

		return health;
	}

	std::string Entity::GetName()
	{

		return *Memory::Ptr<char**>(this, OFFSET_NAME);
	}

	//#define OFFSET_SkeletonActors 0x5E0
	//#define OFFSET_SkeletonStarts  0x250
	//#define OFFSET_SkeletonInfos  0x50
	//#define OFFSET_BoneInfo  0x28

	Vector3& Entity::GetHead()
	{
		Vector3 Empty = Vector3(0, 0, 0);
		auto actor = *Memory::Ptr<DWORD**>(this, OFFSET_SkeletonActors);
		if (!actor)
			return Empty;
		auto Starts = *Memory::Ptr<DWORD**>(actor, OFFSET_SkeletonStarts);
		if (!Starts)
			return Empty;
		auto Skeleton = *Memory::Ptr<DWORD**>(Starts, OFFSET_SkeletonInfos);
		if (!Skeleton)
			return Empty;
		auto Bone = *Memory::Ptr<DWORD**>(Skeleton, OFFSET_BoneInfo);
		if (!Bone)
			return Empty;
		auto Head = *Memory::Ptr<Vector3*>(Bone, OFFSET_HEAD);
		return Head;
	}

	Vector3 Entity::GetHeadFixed()
	{
		Vector3 Empty = Vector3(0, 0, 0);
		auto actor = *Memory::Ptr<DWORD**>(this, OFFSET_SkeletonActors);
		if (!actor)
			return Empty;
		auto Starts = *Memory::Ptr<DWORD**>(actor, OFFSET_SkeletonStarts);
		if (!Starts)
			return Empty;
		auto Skeleton = *Memory::Ptr<DWORD**>(Starts, OFFSET_SkeletonInfos);
		if (!Skeleton)
			return Empty;
		auto Bone = *Memory::Ptr<DWORD**>(Skeleton, OFFSET_BoneInfo);
		if (!Bone)
			return Empty;
		D3DXVECTOR3 Head = *Memory::Ptr<D3DXVECTOR3*>(Bone, OFFSET_HEAD); // specify that we pass by value

		D3DXMATRIX RotateY;
		float Yaw = this->GetYaw();
		D3DXMatrixRotationY(&RotateY, (Yaw - M_PI));
		D3DXVECTOR3 HeadFixed;
		D3DXVec3TransformCoord(&HeadFixed, &Head, &RotateY);

		return *(Vector3*)&HeadFixed;

	}

	float& Entity::Speed()
	{
		return *Memory::Ptr<float*>(this, OFFSET_SPEED);
	}

	DWORD Entity::GetType()
	{
		return *Memory::Ptr<DWORD*>(this, OFFSET_TYPE);
	}

	Vector3& Entity::GetCarPos()
	{
		return *Memory::Ptr<Vector3*>(this, OFFSET_CARPOS);
	}
	Vector3& Entity::GetItemPos()
	{
		return *Memory::Ptr<Vector3*>(this, OFFSET_ITEMPOS);
	}
	Vector3& Entity::GetVelocity()
	{
		return *Memory::Ptr<Vector3*>(this, OFFSET_VELOCITY);
	}
	float& Entity::GetYaw()
	{
		return *Memory::Ptr<float*>(this, OFFSET_YAW);
	}
	float& Entity::GetPitch()
	{
		return *Memory::Ptr<float*>(this, OFFSET_PITCH);
	}
	//0 - stand
	//2 - walk
	//3 - run
	//1 - crouch
	//5 - crouch move
	//6 - prone
	//7 - prone move
	//4 - jump
	int& Entity::GetStance()
	{
		return *Memory::Ptr<int*>(this, OFFSET_STANCE);
	}

	std::vector<Vector3> Entity::GetBones()
	{
		std::vector<Vector3> Empty = {};
		auto actor = *Memory::Ptr<DWORD**>(this, OFFSET_SkeletonActors);
		if (!actor)
			return Empty;
		auto Starts = *Memory::Ptr<DWORD**>(actor, OFFSET_SkeletonStarts);
		if (!Starts)
			return Empty;
		auto Skeleton = *Memory::Ptr<DWORD**>(Starts, OFFSET_SkeletonInfos);
		if (!Skeleton)
			return Empty;
		auto Bone = *Memory::Ptr<DWORD**>(Skeleton, OFFSET_BoneInfo);
		if (!Bone)
			return Empty;


		std::vector<Vector3> retVec = {};
		for (int i = 0; i < 500; i++) {

			D3DXVECTOR3 Pos = *Memory::Ptr<D3DXVECTOR3*>(Bone, i * sizeof(D3DXVECTOR3)); // specify that we pass by value

			if (!Pos)
				break;

			D3DXMATRIX RotateY;
			float Yaw = this->GetYaw();
			D3DXMatrixRotationY(&RotateY, (Yaw - M_PI));
			D3DXVECTOR3 HeadFixed;
			D3DXVec3TransformCoord(&HeadFixed, &Pos, &RotateY);

			retVec.push_back(*(Vector3*)&HeadFixed);

		}

		return retVec;
	}
}