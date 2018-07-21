/**
* H1Z1 SDK
* Made by M0rtale
*/

#pragma once

#include <windows.h>
#include "Matrix4x4.h"

#include "Offsets.h"
#include "Memory.h"
#include "Helpers.h"
#include "D3dx9math.h"

namespace Engine
{
	class CGraphics
	{
	public:
		Vector3 W2S(Vector3 vIn);

		void SetCamera(Vector3 vIn); // world Vector3 Position

		static CGraphics* GetInstance();
	};
}