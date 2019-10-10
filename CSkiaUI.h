/*
	Author: Bill Tong
*/

#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include "CWindow.h"
#include "GlobalVar.h"

static SkBitmap bitmap;

int UpdateMenu(void* data);
SkBitmap DrawMenu(int w, int h);

