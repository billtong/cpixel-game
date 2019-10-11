#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include <core/SkString.h>
#include <core/SkTextBlob.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>

#include "CWindow.hpp"
#include "CButton.hpp"
#include "variables.h"

#include "GameLvlZero.h"

static CWindow* g_InitWindow = new CWindow;
static SkBitmap g_iBmpMenu;
static CButton g_iBtnStart("Start Game", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 250 });
static CButton g_iBtnCtrl("Controls", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 350 });
static CButton g_iBtnCrdt("Credits", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 450 });

int UpdateMenuUI(void* data);
SkBitmap DrawMenu(int w, int h);

void InitMenu();
