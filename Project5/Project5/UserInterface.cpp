#include "UserInterface.h"
#include "Settings.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

UserInterface* UserInterface::m_pInstance;

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::SetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

		style.WindowPadding = ImVec2(15, 15);
		style.WindowRounding = 5.0f;
		style.FramePadding = ImVec2(5, 5);
		style.FrameRounding = 4.0f;
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;

		style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.09f, 0.88f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.09f, 0.88f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.06f, 0.05f, 0.07f, 0.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void UserInterface::TextColor(bool active)
{
	auto& style = ImGui::GetStyle();

	if (active)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);
	}
	else
		style.Colors[ImGuiCol_Text] = ImVec4(0.39f, 0.39f, 0.39f, 1.f);
}

//this->bESPEnabled = false;
//
//this->bESPBox = false;
//this->bESPHealth = false;
//this->bESPName = false;
//this->bESPDistance = false;
//this->bESPHead = false;
//this->bESPSnapline = false;
//this->bESPSpottedEsp = false;
//
//this->bVisualsCrosshair = false;
//this->bVisualsFPS = false;
//
//this->bAccuracyNoSpread = false;
//this->fSpread = 1.f;
//this->bAccuracyNoRecoil = false;
//this->fRecoil = 1.f;
//
//this->bAimEnable = false;

void UserInterface::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	auto& style = ImGui::GetStyle();
	int W, H;
	W = io.DisplaySize.x;
	H = io.DisplaySize.y;

	if (Settings::GetInstance()->Menu)
	{
		ImGui::Begin(XorStr("BOIHOOK | Project NoEye"), &Settings::GetInstance()->Menu, ImVec2(320, 720), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		{
			ImGui::Text(XorStr("ESP"));
			ImGui::Checkbox(XorStr("ESP Enabled"), &Settings::GetInstance()->bESPEnabled);
			ImGui::Checkbox(XorStr("Box"), &Settings::GetInstance()->bESPBox);
			ImGui::Checkbox(XorStr("Health"), &Settings::GetInstance()->bESPHealth);
			ImGui::Checkbox(XorStr("Name"), &Settings::GetInstance()->bESPName);
			ImGui::Checkbox(XorStr("Distance"), &Settings::GetInstance()->bESPDistance);
			ImGui::Checkbox(XorStr("Head"), &Settings::GetInstance()->bESPHead);
			ImGui::Checkbox(XorStr("SnapLine"), &Settings::GetInstance()->bESPSnapline);
			ImGui::Separator();
			ImGui::Text(XorStr("Misc"));
			ImGui::Checkbox(XorStr("FPS"), &Settings::GetInstance()->bVisualsFPS);
			ImGui::Checkbox(XorStr("DebugInfo"), &Settings::GetInstance()->bVisualsDebugInfo);
			ImGui::Checkbox(XorStr("Crosshair"), &Settings::GetInstance()->bVisualsCrosshair);
			ImGui::Checkbox(XorStr("Aim"), &Settings::GetInstance()->bVisualsAimFov);
			ImGui::Checkbox(XorStr("Speed"), &Settings::GetInstance()->bMiscSpeed);
			ImGui::SliderFloat(XorStr("Speed"), &Settings::GetInstance()->fMiscSpeed, 1.f, 2.f, "%0.2f");
			ImGui::Checkbox(XorStr("White List"), &Settings::GetInstance()->bMiscWhiteList);

			ImGui::NextColumn();
			ImGui::Text(XorStr("Item"));
			ImGui::Checkbox(XorStr("Car"), &Settings::GetInstance()->bITEMCar);
			ImGui::Checkbox(XorStr("Weapon"), &Settings::GetInstance()->bITEMWeapon);
			ImGui::Checkbox(XorStr("Other"), &Settings::GetInstance()->bITEMOther);

		}
		ImGui::End(); //End main window



	}
}

UserInterface* UserInterface::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new UserInterface();

	return m_pInstance;
}