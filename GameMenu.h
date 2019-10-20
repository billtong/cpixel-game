#pragma once

#include "CMenuScene.hpp"
#include "variables.h"
#include "Game.h"

using std::vector;

static CWindow* g_iWindow = new CWindow;
static CMenuScene g_iMenuScene;
int UpdateMenuUI(void* data);
void InitMenu();
