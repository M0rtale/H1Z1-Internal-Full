
#include "CGraphics.h"


namespace Engine
{
	CGraphics* CGraphics::GetInstance()
	{
		return *reinterpret_cast<CGraphics**>(ADDRESS_CGRAPHICS/* + reinterpret_cast<uint64_t>(GetModuleHandle(NULL))*/);
	}

	Vector3 CGraphics::W2S(Vector3 vIn)
	{
		auto Graphicss = *Memory::Ptr<DWORD**>(this, OFFSET_CAMERA);
		if (!Graphicss)
			return Vector3(0, 0, 0);
		auto Camera = *Memory::Ptr<DWORD**>(Graphicss, OFFSET_MATRIX);
		if (!Camera)
			return Vector3(0, 0, 0);
		D3DXMATRIX Matrix = *Memory::Ptr<D3DXMATRIX*>(Camera, OFFSET_MATRIX_DEF);
		if (!Matrix)
			return Vector3(0, 0, 0);

		ImGuiIO& io = ImGui::GetIO();

		int ScreenWidth, ScreenHeight;
		ScreenWidth = io.DisplaySize.x; //width
		ScreenHeight = io.DisplaySize.y; //height

		D3DXMatrixTranspose(&Matrix, &Matrix);

		Matrix4x4 vMatrix = *(Matrix4x4*)&Matrix;

		vMatrix._21 *= -1;
		vMatrix._22 *= -1;
		vMatrix._23 *= -1;
		vMatrix._24 *= -1;

		float w = vMatrix.GetAxis(3).Dot(vIn) + vMatrix.m[3][3];

		if (w < 0.098) {
			return Vector3();
		}

		float x = vMatrix.GetAxis(0).Dot(vIn) + vMatrix.m[0][3];
		float y = vMatrix.GetAxis(1).Dot(vIn) + vMatrix.m[1][3];

		Vector3 vOut = Vector3();

		vOut.x = (ScreenWidth / 2) * (1.0 + x / w);
		vOut.y = (ScreenHeight / 2) * (1.0 - y / w);

		return vOut;
	}

	void CGraphics::SetCamera(Vector3 vIn)
	{
		auto Graphicss = *Memory::Ptr<DWORD**>(this, OFFSET_CAMERA);
		if (!Graphicss)
			return;
		auto Camera = *Memory::Ptr<DWORD**>(Graphicss, OFFSET_MATRIX);
		if (!Camera)
			return;
		D3DXMATRIX Matrix = *Memory::Ptr<D3DXMATRIX*>(Camera, OFFSET_MATRIX_DEF);
		if (!Matrix)
			return;

		ImGuiIO& io = ImGui::GetIO();

		int ScreenWidth, ScreenHeight;
		ScreenWidth = io.DisplaySize.x; //width
		ScreenHeight = io.DisplaySize.y; //height

		D3DXMatrixTranspose(&Matrix, &Matrix);

		Matrix4x4 vMatrix = *(Matrix4x4*)&Matrix;

		vMatrix._21 *= -1;
		vMatrix._22 *= -1;
		vMatrix._23 *= -1;
		vMatrix._24 *= -1;

		float w = vMatrix.GetAxis(3).Dot(vIn) + vMatrix.m[3][3];

		if (w < 0.098) {
			return;
		}

		float x = vMatrix.GetAxis(0).Dot(vIn) + vMatrix.m[0][3];
		float y = vMatrix.GetAxis(1).Dot(vIn) + vMatrix.m[1][3];

		Vector3 vOut = Vector3();

		vOut.x = (ScreenWidth / 2) * (1.0 + x / w);
		vOut.y = (ScreenHeight / 2) * (1.0 - y / w);

		


	}
}