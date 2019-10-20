#pragma once

#include "CGameScene.hpp"

void bootstrap(CWindow* window);

int UpdateGameLevelZeroUI(void* data);
vector<CWall> LoadGameLevelZeroWalls();

static CPlayer g_iPlayer(INT_MAX, "Player1", RGBTable.red, 0, 350);
static CGameScene g_iLvlZero(LoadGameLevelZeroWalls());
