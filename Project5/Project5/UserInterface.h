/**
* Overlord Project
* Copyright (C) 2016-2017 RangeMachine
*/

#pragma once

#include "stdfx.h"

class UserInterface
{
public:
	void SetStyle();
	void Render();

	static UserInterface* GetInstance();

private:
	void TextColor(bool active);
	UserInterface();
	~UserInterface();

	static UserInterface* m_pInstance;
};