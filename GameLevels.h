#pragma once

#include "CScene.hpp"

static CPlayer g_iPlayer(INT_MAX, "Player1", RGBTable.red, 0, 350);
static CGameScene g_iLvlZero("");

void bootstrap(CWindow* window);
int UpdateGameLevelZeroUI(void* data);