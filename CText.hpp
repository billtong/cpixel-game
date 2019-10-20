#pragma once

#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>
#include <string>
#include"CPoint.hpp"

using std::string;

class CText
{
public:
	const int* m_gTextRGB;
	int m_nTextSize;
	CPoint m_pPosition;
	string m_stText;

	void DrawText(SkCanvas& canvas, SkPaint& paint)
	{
		paint.setTextSize(m_nTextSize);
		paint.setARGB(0xFF, m_gTextRGB[0], m_gTextRGB[1], m_gTextRGB[2]);
		canvas.drawString(m_stText.c_str(), m_pPosition.m_iX, m_pPosition.m_iY, paint);
	}
};