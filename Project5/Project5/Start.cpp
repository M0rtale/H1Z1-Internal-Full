#include "Start.h"

ID3D11Device *Start::pDevice = NULL;
ID3D11DeviceContext *Start::pContext = NULL;
IDXGISwapChain* Start::pSwapChain = NULL;
ID3D11RenderTargetView* Start::pRenderTargetView = NULL;

DWORD Start::Initialise(LPVOID in)
{
	AllocConsole();
	freopen("CON", "w", stdout);
	SetConsoleTitleA(XorStr("Project NoEye"));

	Helpers::Log(XorStr("Cheat Initialised"));
	Helpers::Log(XorStr("Cheat Made By BOI"));

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	HWND hWindow = FindWindow(XorStr("H1Z1 PlayClient (Live)"), NULL);

#pragma region Initialise DXGI_SWAP_CHAIN_DESC
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // sets color formatting, we are using RGBA
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // says what we are doing with the buffer
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // msdn explains better than i can: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173076(v=vs.85).aspx
	scd.OutputWindow = hWindow; // our gamewindow, obviously
	scd.SampleDesc.Count = 1; // Set to 1 to disable multisampling
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // D3D related stuff, cant really describe what it does
	scd.Windowed = ((GetWindowLongPtr(hWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true; // check if our game is windowed
	scd.BufferDesc.Width = 1920; // temporary width
	scd.BufferDesc.Height = 1080; // temporary height
	scd.BufferDesc.RefreshRate.Numerator = 144; // refreshrate in Hz
	scd.BufferDesc.RefreshRate.Denominator = 1; // no clue, lol
#pragma endregion

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		NULL, &featureLevel, 1, D3D11_SDK_VERSION,
		&scd, &Start::pSwapChain,
		&Start::pDevice, NULL, &Start::pContext
	)))
	{
		Helpers::LogError(XorStr("D3D11CreateDevice"));
		return 0;
	}

	// GET VTABLE POINTERS
	DWORD_PTR*  pSwapChainVT = reinterpret_cast<DWORD_PTR*>(Start::pSwapChain);
	DWORD_PTR*  pDeviceVT = reinterpret_cast<DWORD_PTR*>(Start::pDevice);
	DWORD_PTR*  pContextVT = reinterpret_cast<DWORD_PTR*>(Start::pContext);

	pSwapChainVT = reinterpret_cast<DWORD_PTR*>(pSwapChainVT[0]);
	pDeviceVT = reinterpret_cast<DWORD_PTR*>(pDeviceVT[0]);
	pContextVT = reinterpret_cast<DWORD_PTR*>(pContextVT[0]);

	Helpers::LogAddress(XorStr("pSwapChainVT"), reinterpret_cast<int64_t>(pSwapChainVT));
	Helpers::LogAddress(XorStr("pDeviceVT"), reinterpret_cast<int64_t>(pDeviceVT));
	Helpers::LogAddress(XorStr("pContextVT"), reinterpret_cast<int64_t>(pContextVT));

	Helpers::LogAddress(XorStr("D3D11SWAPCHAIN"), pSwapChainVT[8]);
	Helpers::LogAddress(XorStr("D3D11CONTEXT"), pContextVT[12]);
	Helpers::LogAddress(XorStr("D3D11DEVICE"), pDeviceVT[24]);

	// SET MISC FUNCTIONS
	Renderer::GetInstance()->Initialize();
	UserInterface::GetInstance()->SetStyle();
	Input::GetInstance()->StartThread();

	// GET FUNCTIONS
	Hooks::oPresent = reinterpret_cast<tD3D11Present>(pSwapChainVT[8]/*D3D11PRESENT*/);

	// LETS HOOK IT
	Helpers::HookFunction(reinterpret_cast<PVOID*>(&Hooks::oPresent), Hooks::hkD3D11Present);

	Hooks::oriWndProc = SetWindowLongPtr(FindWindow(XorStr("H1Z1 PlayClient (Live)"), NULL), GWLP_WNDPROC, (LONG_PTR)Hooks::WndProc);
	return 0;
}

void Start::Release()
{
	// RELEASE CONSOLE
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();

	// KILL STILL RUNNING TREADS
	Input::GetInstance()->StopThread();

	// UNHOOK THE FUNCTIONS
	Helpers::UnhookFunction(reinterpret_cast<PVOID*>(&Hooks::oPresent), Hooks::hkD3D11Present);

	if (Hooks::oriWndProc)
		SetWindowLongPtr(FindWindow(XorStr("H1Z1 PlayClient (Live)"), NULL), GWLP_WNDPROC, Hooks::oriWndProc);
	Hooks::oriWndProc = 0;
}
