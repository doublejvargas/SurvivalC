#pragma once

#include "DisplayManager.h"

class ApplicationManager
{
public:
	ApplicationManager();
	virtual ~ApplicationManager();

	void Start();

private:
	DisplayManager* m_DisplayManager = nullptr;
};
