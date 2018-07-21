#include "stdfx.h"
#include "Hooks.h"
#include "Helpers.h"
#include "start.h"
#include "Renderer.h"
#include "UserInterface.h"
#include <intrin.h>

tD3D11Present Hooks::oPresent = NULL;
LONG_PTR Hooks::oriWndProc = NULL;
bool Hooks::PressedKeys[256] = {};
bool bOnce = false;
HRESULT __stdcall Hooks::hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	if (!bOnce)
	{
		HWND hWindow = FindWindow(XorStr("H1Z1 PlayClient (Live)"), NULL);
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&Start::pDevice)))
		{
			pSwapChain->GetDevice(__uuidof(Start::pDevice), (void**)&Start::pDevice);
			Start::pDevice->GetImmediateContext(&Start::pContext);
		}

		ID3D11Texture2D* renderTargetTexture = nullptr;
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
		{
			Start::pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &Start::pRenderTargetView);
			renderTargetTexture->Release();
		}
	
		ImGui_ImplDX11_Init(hWindow, Start::pDevice, Start::pContext);
		ImGui_ImplDX11_CreateDeviceObjects();

		Helpers::Log(XorStr("D3D11Present initialised"));
		bOnce = true;

		
	}

	

	Start::pContext->OMSetRenderTargets(1, &Start::pRenderTargetView, NULL);

	//Helpers::Log("OMSetRenderTargets Succeded");

	ImGui_ImplDX11_NewFrame();

	//Input::MenuKeyMonitor();

	//Helpers::Log("New Frame Succeeded");

	Renderer::GetInstance()->BeginScene();
	//Helpers::Log("BeginScene Succeeded");
	Renderer::GetInstance()->DrawScene();
	//Helpers::Log("DrawScene Succeeded");
	Renderer::GetInstance()->EndScene();

	//Helpers::Log("EndScene Succeeded");

	UserInterface::GetInstance()->Render();

	//Helpers::Log("render Succeeded");

	ImGui::Render();

	//Helpers::Log("ImGui EndScene Succeeded");

	return Hooks::oPresent(pSwapChain, SyncInterval, Flags);
}

LRESULT __stdcall Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Helpers::Log("Wndproc called");

	switch (uMsg) // record window message
	{
	case WM_LBUTTONDOWN:
		Hooks::PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		Hooks::PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		Hooks::PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		Hooks::PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		Hooks::PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		Hooks::PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			Hooks::PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			Hooks::PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			Hooks::PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			Hooks::PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		Hooks::PressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		Hooks::PressedKeys[wParam] = false;
		break;
	default:
		break;
	}
	return CallWindowProcW((WNDPROC)Hooks::oriWndProc, hWnd, uMsg, wParam, lParam);
}