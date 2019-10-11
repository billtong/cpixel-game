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

int UpdateGameLvlZero(void* data);
SkBitmap DrawGameLvlZero(int w, int h);

void InitGameLvlZero(CWindow * window);
