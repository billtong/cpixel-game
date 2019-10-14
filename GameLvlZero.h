#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include <core/SkString.h>
#include <core/SkTextBlob.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkPath.h>

#include "CWindow.hpp"
#include "CButton.hpp"
#include "CPlayer.hpp"
#include "variables.h"

static SkBitmap g_iBmpLvlZero;

static CPlayer g_iPlayer;

int UpdateGameLvlZeroUI(void* data);
SkBitmap DrawGameLvlZero(int w, int h);

int UpdateGForce(void* data);

void InitGameLvlZero(CWindow * window);
