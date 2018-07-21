/**
* Overlord Project
* Copyright (C) 2016-2017 RangeMachine
*/

#pragma once

#include "stdfx.h"

class Input
{
public:
	static Input* GetInstance();

	void StartThread();
	void StopThread();

	Input();
	~Input();

	static void MenuKeyMonitor();

private:
	

	HANDLE m_hThread;

	static Input* m_pInstance;
};
