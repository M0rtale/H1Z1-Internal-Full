#include "Renderer.h"
//#include "Entity.h"
//#include "GameManager.h"
//#include "GameRenderer.h"
#include "Settings.h"
#include "Rubik.h"
#include "Visual.h"
//#include "Accuracy.h"

Renderer* Renderer::m_pInstance;


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGuiStyle& style = ImGui::GetStyle();

	// This is my example of font initializing
	// First font used for UI
	// Second for rendering, 32.0f is pixel size, not font size.
	io.Fonts->AddFontFromMemoryTTF(g_fRubik, sizeof(g_fRubik), 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_pDefault = io.Fonts->AddFontFromMemoryTTF(g_fRubik, sizeof(g_fRubik), 15.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_pTabs = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahomabd.ttf", 62.f);
	m_pSubTabs = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 25.f);
}

void Renderer::BeginScene()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("D3D11_Buffer", reinterpret_cast<bool*>(true), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiSetCond_Always);
}

void Renderer::DrawScene()
{
	//visuals and esp

	Visuals::GetInstance()->GetInstance()->VisualsMain();
}

void Renderer::EndScene()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();

	ImGui::End();
	ImGui::PopStyleColor();
}

void Renderer::DrawBox(const ImVec2& pos, const ImVec2& headPosition, uint32_t color)
{
	float width = (headPosition.y + 15 - pos.y) / 4.5f;

	//Draw box
	DrawLine(ImVec2(pos.x - width, pos.y), ImVec2(pos.x + width, pos.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x - width, pos.y), 0x00000000, 2.0f);

	DrawLine(ImVec2(pos.x + width, headPosition.y), ImVec2(pos.x + width, pos.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x + width, headPosition.y), 0x00000000, 2.0f);

	//Draw box
	DrawLine(ImVec2(pos.x - width, pos.y), ImVec2(pos.x + width, pos.y), color, 1.5f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x - width, pos.y), color, 1.5f);

	DrawLine(ImVec2(pos.x + width, headPosition.y), ImVec2(pos.x + width, pos.y), color, 1.5f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x + width, headPosition.y), color, 1.5f);
}

//void Renderer::DrawBox(const std::vector<Engine::Vector3>& bones, const Engine::Vector3& base, uint32_t color) // 3d
//{
//	auto pGraphics = Engine::CGraphics::GetInstance();
//
//	Engine::Vector3 min = Engine::Vector3(9999, 9999, 9999), max = Engine::Vector3(-9999, -9999, -9999);
//
//	for (Engine::Vector3 bone : bones)
//	{
//		if (bone.x < min.x)
//			min.x = bone.x;
//		if (bone.y < min.y)
//			min.y = bone.y;
//		if (bone.z < min.z)
//			min.z = bone.z;
//		if (bone.x > max.x)
//			max.x = bone.x;
//		if (bone.y > max.y)
//			max.y = bone.y;
//		if (bone.z > max.z)
//			max.z = bone.z;
//	}
//
//	min += base;
//	max += base;
//
//	/*
//	   .5------8
//	 .' |    .'|
//	6---+--7'  |
//	|   |  |   |
//	|  ,4--+---3
//	|.'    | .'
//	1------2'
// 
//	1 = min
//	8 = max
// 
//*/
//
//	Engine::Vector3 crnr2 = Engine::Vector3(max.x, min.y, min.z);
//	Engine::Vector3 crnr3 = Engine::Vector3(max.x, min.y, max.z);
//	Engine::Vector3 crnr4 = Engine::Vector3(min.x, min.y, max.z);
//	Engine::Vector3 crnr5 = Engine::Vector3(min.x, max.y, max.z);
//	Engine::Vector3 crnr6 = Engine::Vector3(min.x, max.y, min.z);
//	Engine::Vector3 crnr7 = Engine::Vector3(max.x, max.y, min.z);
//
//	crnr2 = pGraphics->W2S(crnr2);
//	crnr3 = pGraphics->W2S(crnr3);
//	crnr4 = pGraphics->W2S(crnr4);
//	crnr5 = pGraphics->W2S(crnr5);
//	crnr6 = pGraphics->W2S(crnr6);
//	crnr7 = pGraphics->W2S(crnr7);
//	min = pGraphics->W2S(min);
//	max = pGraphics->W2S(max);
//
//	//From min to 2, 4 and 6
//	DrawLine(ImVec2(min.x, min.y), ImVec2(crnr2.x, crnr2.y), color, 1.5f);
//	DrawLine(ImVec2(min.x, min.y), ImVec2(crnr4.x, crnr4.y), color, 1.5f);
//	DrawLine(ImVec2(min.x, min.y), ImVec2(crnr6.x, crnr6.y), color, 1.5f);
//
//	//From max to 5, 7 and 3
//	DrawLine(ImVec2(max.x, max.y), ImVec2(crnr5.x, crnr5.y), color, 1.5f);
//	DrawLine(ImVec2(max.x, max.y), ImVec2(crnr7.x, crnr7.y), color, 1.5f);
//	DrawLine(ImVec2(max.x, max.y), ImVec2(crnr3.x, crnr3.y), color, 1.5f);
//
//	//From 2 to 7 and 3
//	DrawLine(ImVec2(crnr2.x, crnr2.y), ImVec2(crnr7.x, crnr7.y), color, 1.5f);
//	DrawLine(ImVec2(crnr2.x, crnr2.y), ImVec2(crnr3.x, crnr3.y), color, 1.5f);
//
//	//From 4 to 5 and 3
//	DrawLine(ImVec2(crnr4.x, crnr4.y), ImVec2(crnr5.x, crnr5.y), color, 1.5f);
//	DrawLine(ImVec2(crnr4.x, crnr4.y), ImVec2(crnr3.x, crnr3.y), color, 1.5f);
//
//	//From 6 to 5 and 7
//	DrawLine(ImVec2(crnr6.x, crnr6.y), ImVec2(crnr5.x, crnr5.y), color, 1.5f);
//	DrawLine(ImVec2(crnr6.x, crnr6.y), ImVec2(crnr7.x, crnr7.y), color, 1.5f);
//}

float Renderer::DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	std::stringstream steam(text);
	std::string line;
	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		if (center)
		{
			window->DrawList->AddText(pFont, size + 0.2f, ImVec2(pos.x - textSize.x / 2.0f - 1, pos.y + textSize.y * i - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}
		else
		{
			window->DrawList->AddText(pFont, size + 0.2f, ImVec2(pos.x - 1, pos.y + textSize.y * i - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}

	return y;
}

float Renderer::DrawsText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	std::stringstream steam(text);
	std::string line;
	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		if (center)
		{
			window->DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}
		else
		{
			window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}

	return y;
}

void Renderer::DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}

void Renderer::DrawHealth(const ImVec2& scalepos, const ImVec2& scaleheadPosition, INT8 health, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	uint32_t backcolor = 0xFF555656;
	uint32_t color = 0xFF009B1C;

	// 2 + 2 = 4 - 1 = 3 quick mathzzz
	float width = (scaleheadPosition.y + 15 - scalepos.y) / 4.5f;
	float healthwidth1 = (scalepos.y - scaleheadPosition.y);
	float healthwidth2 = healthwidth1 / 120;
	float defhealthwidth = healthwidth2 * health;

	DrawLine(ImVec2(scalepos.x - width + 5, scaleheadPosition.y), ImVec2(scalepos.x - width + 5, scalepos.y), backcolor, 2.5f);
	DrawLine(ImVec2(scalepos.x - width + 5, scalepos.y - defhealthwidth), ImVec2(scalepos.x - width + 5, scalepos.y), color, 2.5f);
}

void Renderer::DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), 12, thickness);
}

void Renderer::DrawCircleScale(const ImVec2& position, float radius, uint32_t color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness)
{
	float rad = (scaleheadPosition.y + 15 - scalepos.y) / 10.5f;
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddCircle(position, rad, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), 12, thickness);
}

void Renderer::DrawCircleFilled(const ImVec2& position, float radius, uint32_t color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	 float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), 12);
}

Renderer* Renderer::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Renderer();

	return m_pInstance;
}