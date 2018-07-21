/**
* Overlord Project
* Copyright (C) 2016-2017 RangeMachine
*/

#pragma once

#include "Input.h"
#include "Settings.h"

#include "ImGui/imgui.h"

Input* Input::m_pInstance;

Input::Input()
{

}

Input::~Input()
{

}

void Input::StartThread()
{
	m_hThread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MenuKeyMonitor), NULL, NULL, NULL);
}

void Input::StopThread()
{
	TerminateThread(m_hThread, 0);
}

void Input::MenuKeyMonitor()
{
	HWND gameWindow = FindWindow(XorStr("H1Z1 PlayClient (Live)"), NULL);

	while (true)
	{
		if (Settings::GetInstance()->Menu)
		{
			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(gameWindow, &mousePosition);

			ImGuiIO& io = ImGui::GetIO();
			io.MousePos.x = mousePosition.x;
			io.MousePos.y = mousePosition.y;

			if (Hooks::PressedKeys[VK_LBUTTON])
				io.MouseDown[0] = true;
			else
				io.MouseDown[0] = false;
		}
		else
		{
			std::this_thread::sleep_for(
				std::chrono::milliseconds(250));
		}

		if (Hooks::PressedKeys[VK_INSERT])
		{
			Settings::GetInstance()->Menu = !Settings::GetInstance()->Menu;

			std::this_thread::sleep_for(
				std::chrono::milliseconds(250));
		}
	}
}

Input* Input::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Input();

	return m_pInstance;
}