#pragma once

#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include "entity.hpp"
#include "variables.h"

class CLava
{
public:
	const int m_nHeight;
	const int* m_gRGB;
public:
	CLava(const int* rgb, const int height) : m_gRGB(rgb), m_nHeight(height) {}
	void Draw(SkCanvas& canvas, SkPaint& paint, SkScalar w, SkScalar h)
	{
		SkRRect rrect = SkRRect::MakeRect({ 0, h - m_nHeight, w,  h });
		paint.setARGB(0xFF, m_gRGB[0], m_gRGB[1], m_gRGB[2]);
		canvas.drawRRect(rrect, paint);
	}
};