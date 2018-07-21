#pragma once
#include "stdfx.h"
#undef DrawText

class Renderer
{
public:
	void Initialize();

	void BeginScene();
	void DrawScene();
	void EndScene();
	//void SetScene();

	float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& position, float size, uint32_t color, bool center);
	float DrawsText(ImFont* pFont, const std::string& text, const ImVec2& position, float size, uint32_t color, bool center);
	void DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
	void DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f);
	void DrawCircleScale(const ImVec2& position, float radius, uint32_t color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness = 1.0f);
	void DrawCircleFilled(const ImVec2& position, float radius, uint32_t color);
	void DrawBox(const ImVec2& position, const ImVec2& headPosition, uint32_t color);
	//void DrawBox(const std::vector<Engine::Vector3>& bones, const Engine::Vector3& base, uint32_t color);
	void DrawHealth(const ImVec2& scalepos, const ImVec2& scaleheadPosition, INT8 health, float thickness = 1.0f);

	ImFont* m_pDefault;
	ImFont* m_pTabs;
	ImFont* m_pSubTabs;

	static Renderer* GetInstance();

private:
	Renderer();
	~Renderer();

	static Renderer* m_pInstance;
};