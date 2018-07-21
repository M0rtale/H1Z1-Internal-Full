#include "Visual.h"
#include "MakeJMP.h"

Visuals* Visuals::m_pInstance;

Visuals::Visuals()
{
}

Visuals::~Visuals()
{
}

void Visuals::VisualsMain()
{
	Visuals::DrawPlayers();
	//Helpers::Log("DrawESP Succeeded");
	Visuals::DrawVisuals();
	//Helpers::Log("DrawVisuals Succeeded");
	Visuals::Misc();
	Visuals::DrawObjects();
}

void Visuals::DrawObjects()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//Helpers::Log(XorStr("DrawESP"));

	auto pCGame = Engine::CGame::GetInstance();
	//Helpers::Log(XorStr("CGaME"));
	auto pCGraphics = Engine::CGraphics::GetInstance();

	std::vector<Engine::Entity*> list = pCGame->GetObjects();

	for (int i = 0; i < list.size() && list.at(i) != nullptr && list.at(i) && Engine::Memory::IsValidPtr<Engine::Entity>(list.at(i)); i++)
	{
		DWORD type = list.at(i)->GetType();

		if (Settings::GetInstance()->bITEMWeapon && (type == TYPE_Weapon) && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"),list.at(i)->GetName() , distance), ImVec2(Position.x, Position.y), 16.f, 0xFF00FF00, true);
		}
		if (Settings::GetInstance()->bITEMOther && (type == TYPE_Ammo || type == TYPE_Grenade || type == TYPE_ITEM) && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xFF0000FF, true);
		}
		if (Settings::GetInstance()->bITEMCar && (type == TYPE_OffRoader || type == TYPE_CAR_2 || type == TYPE_CAR_3 || type == TYPE_ATV) && list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition())< 700.f)
		{
			Engine::Vector3 loc = list.at(i)->GetCarPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xFFFF0000, true);
		}
	}
}


void Visuals::AIM(float x, float y)
{

}
void Visuals::Misc()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	auto pCGame = Engine::CGame::GetInstance();
	auto pCGraphics = Engine::CGraphics::GetInstance();

	if (Hooks::PressedKeys[VK_SHIFT]) // speed
	{
		MakeNOP((BYTE*)0x14160D514, 0x8);
	}
	else
	{
		BYTE RestoreSpeed[8] = { 0xF3, 0x0F, 0x11, 0x86, 0xD8, 0x45, 0x00, 0x00 }; // movss [rsi+000045D8],xmm0

		MakeRestore((BYTE*)0x14160D514, 0x8, RestoreSpeed);
	}

	if (Settings::GetInstance()->bMiscSpeed) // when shift
	{
		if(Hooks::PressedKeys[VK_SHIFT])
			pCGame->GetLocalPlayer()->Speed() = Settings::GetInstance()->fMiscSpeed;
	}
}

float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

void MouseMove(float x, float y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}

//0 - stand
//2 - walk
//3 - run
//1 - crouch
//5 - crouch move
//6 - prone
//7 - prone move
//4 - jump
void Visuals::DrawPlayers()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//Helpers::Log(XorStr("DrawESP"));

	auto pCGame = Engine::CGame::GetInstance();
	//Helpers::Log(XorStr("CGaME"));
	auto pCGraphics = Engine::CGraphics::GetInstance();
	//Helpers::Log(XorStr("CGraphics"));

	Engine::Entity* pLocal = pCGame->GetLocalPlayer();

	//Helpers::Log(XorStr("local"));

	std::vector<Engine::Entity*> list = pCGame->GetPlayers();

	//Helpers::Log(XorStr("list"));

	if (Settings::GetInstance()->bVisualsDebugInfo && pCGame->GetLocalPlayer() != nullptr && pCGame->GetLocalPlayer() && Engine::Memory::IsValidPtr<Engine::Entity>(pCGame->GetLocalPlayer()))
	{
		DWORD health = pCGame->GetLocalPlayer()->GetHealth();
		char Buffer[512];
		sprintf_s(Buffer, "List size: %i", list.size());
		char Buffer1[512];
		sprintf_s(Buffer1, "LocalplayerHealth: %i", health / 100);
		char Buffer2[512];
		sprintf_s(Buffer2, "LocalplayerPosition: %f    %f    %f", pCGame->GetLocalPlayer()->GetPosition().x, pCGame->GetLocalPlayer()->GetPosition().y, pCGame->GetLocalPlayer()->GetPosition().z);
		char Buffer4[512];
		sprintf_s(Buffer4, "LocalplayerSpeed: %f", pCGame->GetLocalPlayer()->Speed());
		char Buffer5[512];
		sprintf_s(Buffer5, "LocalplayerStance: %i", pCGame->GetLocalPlayer()->GetStance());
		char Buffer6[512];
		sprintf_s(Buffer6, "LocalplayerID: %i", pCGame->GetLocalPlayer()->GetID());
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, XorStr("LocalPlayer Name: ") + pCGame->GetLocalPlayer()->GetName(), ImVec2(20, 50), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer, ImVec2(20, 80), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer1, ImVec2(20, 110), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer2, ImVec2(20, 140), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer4, ImVec2(20, 170), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer5, ImVec2(20, 200), 26.f, 0xFF00CE11, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Buffer6, ImVec2(20, 230), 26.f, 0xFF00CE11, false);
	}


	float BestDist = 100;
	int BestTarget = -1;
	Engine::Vector3 AimPos = Engine::Vector3();

	for (int i = 0; i < list.size() && list.at(i) != nullptr && list.at(i) && Engine::Memory::IsValidPtr<Engine::Entity>(list.at(i)); i++)
	{
		//Helpers::LogInt(XorStr("Visual Loop"), i);
		Engine::Entity* pEntity = list.at(i);

		if (pEntity == nullptr || pEntity == pCGame->GetLocalPlayer())
			continue;

		if (WhiteList.end() != std::find(WhiteList.begin(), WhiteList.end(), pEntity->GetName())) // if whitelisted.
			continue;

		DWORD Health = pEntity->GetHealth(); // break

		Health /= 100;

		//Helpers::Log(XorStr("Health"));

		if (Health > 0)
		{
			Engine::Vector3 Position = pCGraphics->W2S(pEntity->GetPosition());

			//Helpers::Log(XorStr("Get Position Check"));

			if (Position.x < 1 || Position.x > io.DisplaySize.x || Position.y < 1 || Position.y > io.DisplaySize.y)
				continue;

			//Helpers::Log(XorStr("off screen Check"));

			Engine::Vector3 HeadPosition = pCGraphics->W2S((pEntity->GetHeadFixed() + pEntity->GetPosition()));

			//Helpers::Log(XorStr("Head Position Check"));
			if (Settings::GetInstance()->bESPEnabled)
			{
				// Draw our Box
				if (Settings::GetInstance()->bESPBox)
				{
					Renderer::GetInstance()->DrawBox(ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y), 0xFFBFFF00);
				}

				// Draw our Head
				if (Settings::GetInstance()->bESPHead)
				{
					Renderer::GetInstance()->DrawCircleScale(ImVec2(HeadPosition.x, HeadPosition.y), 5.f, 0xffcfff3f, ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y));
				}

				float distance = pCGame->GetLocalPlayer()->GetPosition().Distance(pEntity->GetPosition());
				// Draw our Distance
				if (Settings::GetInstance()->bESPDistance)
				{
					Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("Distance: %.1fm"), distance), ImVec2(Position.x, Position.y + 5), 12.f, 0xFFFFFFFF, true);
				}

				// Draw our Health
				if (Settings::GetInstance()->bESPHealth)
				{
					Renderer::GetInstance()->DrawHealth(ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y), Health);
				}

				// Draw SnapLines
				if (Settings::GetInstance()->bESPSnapline)
				{
					Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y), ImVec2(Position.x, Position.y), 0xFFff8d3d);
				}

				// Draw our Name
				if (Settings::GetInstance()->bESPName)
				{
					// Calculations so that our name is at the correct position
					float posoffset = Position.y - HeadPosition.y;
					float posoffset2 = Position.y - posoffset - 15;
					Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, pEntity->GetName(), ImVec2(Position.x, posoffset2), 12.f, 0xFFFFFFFF, true);
				}
			}
			//AIM Semi Pasted, outside ESP if check
			if (Settings::GetInstance()->bVisualsAimFov && WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), pEntity->GetName()))
			{
				Engine::Entity* pEnt = list.at(i);
				Engine::Vector3 Velocity = pEnt->GetVelocity();
				float distance = pCGame->GetLocalPlayer()->GetPosition().Distance(pEnt->GetPosition());

				//Aim, with p2000000 iq prediction

				Engine::Vector3 EnginePrediction = pEnt->GetPosition();

				if (distance < 29)
				{
					EnginePrediction.x += 0;
					EnginePrediction.y += 0;
					EnginePrediction.z += 0;
				}
				else if (distance < 39)
				{
					EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 1.0f);
					EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 1.0f);
					EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 1.0f);
				}
				else if (distance < 100)
				{
					EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 3.5f);
					EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 3.5f);
					EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 3.5f);
				}
				else if (distance > 99)
				{
					EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 15.0f);
					EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 15.0f);
					EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 15.0f);
				}
				else if (distance > 149)
				{
					EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 50.0f);
					EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 50.0f);
					EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 50.0f);
				}

				if (distance > 49)
				{
					float BulletCurve = (0.00365f * distance);
					EnginePrediction.y += BulletCurve;
				}
				Engine::Vector3 HeadPos = pEnt->GetHeadFixed();
				HeadPos += EnginePrediction;

				HeadPos = pCGraphics->W2S(HeadPos);

				float FaggotDist = GetDistance(HeadPos.x, HeadPos.y, io.DisplaySize.x / 2, io.DisplaySize.y / 2);

				if (FaggotDist < BestDist)
				{
					AimPos = HeadPos;
					BestDist = FaggotDist;
					BestTarget = i;
				}
			}
		}
	}

	//move aimbot
	if (BestTarget != -1 && AimPos.x != 0 && AimPos.y != 0 && Hooks::PressedKeys[VK_RBUTTON])
	{
		if (WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), list.at(BestTarget)->GetName()))
		{
			int moveX = AimPos.x - io.DisplaySize.x / 2;
			int moveY = AimPos.y - io.DisplaySize.y / 2;

			MouseMove(moveX, moveY); // because I don't know how to write angle.
		}
	}
	//move whitelist
	if (Settings::GetInstance()->bMiscWhiteList && Hooks::PressedKeys[VK_F2] && BestTarget != -1 && AimPos.x != 0 && AimPos.y != 0)
	{
		if (WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), list.at(BestTarget)->GetName()))
			WhiteList.push_back(list.at(BestTarget)->GetName());
	}
	//clean
	if (Hooks::PressedKeys[VK_F3])
		WhiteList.clear();

	// draw name lists
	if (Settings::GetInstance()->bMiscWhiteList)
	{
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "Press F2 While Aiming at player to add WhiteList", ImVec2(20, 20), 16.f, 0xFFFF00FF, false);
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "Press F3 to clear list", ImVec2(20, 40), 16.f, 0xFFFF00FF, false);
		//draw out our list
		int y = 60;
		for (int i = 0; i < WhiteList.size(); i++, y += 20)
		{
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, WhiteList.at(i), ImVec2(20, y), 16.f, 0xFFFF00FF, false);
		}
	}
}

void Visuals::DrawVisuals()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	//auto pGameManager = Engine::GameManager::GetInstance();
	//auto pStatusManager = Engine::StatusManager::GetInstance();


	// Draw Crosshair
	if (Settings::GetInstance()->bVisualsCrosshair)
	{
		//if (pStatusManager->IsIngame())
		//{
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2 - 15, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 - 5, io.DisplaySize.y / 2), 0xFF00FF2A, 3.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2 + 16, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 + 6, io.DisplaySize.y / 2), 0xFF00FF2A, 3.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 - 15), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 - 5), 0xFF00FF2A, 3.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 + 16), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 + 6), 0xFF00FF2A, 3.f);
		//}
	}

	// Draw FPS
	if (Settings::GetInstance()->bVisualsFPS)
	{
		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText("%.1f", io.Framerate), ImVec2(20, 20), 26.f, 0xFF00CE11, false);
	}
}

Visuals* Visuals::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Visuals();

	return m_pInstance;
}