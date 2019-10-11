#pragma once
#include<string>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>
#ifdef _WIN32

#pragma warning(disable:4996)
#include <SDL.h>
#include <SDL_thread.h>
#else
#include <SDL2/SDL.h>
#endif

using std::string;

typedef struct offset
{
	SkScalar w;
	SkScalar h;
	SkScalar x;
	SkScalar y;
} Offset;

class CButton
{
public:
	string m_stBtnName;
	const int* m_pBtnRGB;
	const int* m_pTxtRGB;
	Offset m_iOffset;
public:
	CButton(string name, const int* btnRgb, const int* txtRgb, Offset offset) {
		m_stBtnName = name;
		m_pBtnRGB = btnRgb;
		m_pTxtRGB = txtRgb;
		m_iOffset = offset;
	}
	void DrawButton(SkCanvas& canvas, SkPaint& paint)
	{
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		SkVector radii[] = { {10, 10}, {10, 10}, {10, 10}, {10, 10} };
		rrect.setRectRadii(rrect.getBounds(), radii);
		SDL_Event e;
		paint.setARGB(0xFF, m_pBtnRGB[0], m_pBtnRGB[1], m_pBtnRGB[2]);
		canvas.drawRRect(rrect, paint);
		paint.setTextSize(40);
		paint.setARGB(0xFF, m_pTxtRGB[0], m_pTxtRGB[1], m_pTxtRGB[2]);
		canvas.drawString(m_stBtnName.c_str(), m_iOffset.x + 50, m_iOffset.y + 40, paint);
	}
	bool ContainsPoint(int x, int y)
	{
		return (x > m_iOffset.x) && (x < m_iOffset.x + m_iOffset.w) && (y > m_iOffset.y) && (y < m_iOffset.y + m_iOffset.h);
	}
};

