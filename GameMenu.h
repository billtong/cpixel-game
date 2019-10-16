#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include <core/SkString.h>
#include <core/SkTextBlob.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>

#include "CWindow.hpp"
#include "CAccessories.hpp"
#include "variables.h"

#include "GameLevels.h"

using std::vector;

static CWindow* g_InitWindow = new CWindow;
static SkBitmap g_iBmpMenu;

static CButton g_iBtnStart("Start Game", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 250 });
static CButton g_iBtnCtrl("Controls", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 350 });
static CButton g_iBtnCrdt("Credits", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 450 });

static vector<CButton> g_gBtn = { g_iBtnStart, g_iBtnCtrl, g_iBtnCrdt };
static vector<CText> g_gTxt;

int UpdateMenuUI(void* data);
void DrawMenu(int w, int h);

void InitMenu();
