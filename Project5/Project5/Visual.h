#pragma once
#include "stdfx.h"
#include "Entity.h"
#include "CGame.h"
#include "CGraphics.h"
//#include "GameManager.h"
//#include "GameRenderer.h"
//#include "StatusManager.h"
//#include "InterfaceManager.h"
#include "Settings.h"
#include "Renderer.h"

class Visuals
{
public:
	void DrawPlayers();
	void DrawVisuals();
	void DrawObjects();
	void Misc();
	void AIM(float x, float y);
	void VisualsMain();

	static Visuals* GetInstance();

private:
	Visuals();
	~Visuals();

	std::vector<std::string> WhiteList;

	static Visuals* m_pInstance;
};