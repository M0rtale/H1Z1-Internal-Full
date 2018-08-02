#pragma once
#include <d3d11.h>
#include "stdfx.h"

namespace Start
{
	//Variables
	extern ID3D11Device *pDevice;
	extern ID3D11DeviceContext *pContext;
	extern IDXGISwapChain* pSwapChain;
	extern ID3D11RenderTargetView* pRenderTargetView;

	//Functions
	DWORD Initialise(LPVOID in);
	void Release();
	void GetResolution(UINT horizontal, UINT vertical);
}
