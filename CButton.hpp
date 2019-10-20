#pragma once

#include <string>
#include <functional>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include"CPoint.hpp"

using std::string;
using std::function;

enum class ButtonState { HOVER, ACTIVE, NORMAL };
const static char* ButtonStateName[3] = { "Hover", "active", "normal" };	/* for debuging only */
class CButton
{
public:
	string m_stName;
	const int* m_pBtnRGB;
	const int* m_pTxtRGB;
	Offset m_iOffset;
	ButtonState m_eState;
	function<void(CWindow*)> m_fnClickCallBack;

	CButton(string name, const int* btnRgb, const int* txtRgb, Offset offset): m_stName(name), m_pBtnRGB(btnRgb), m_pTxtRGB(txtRgb), m_iOffset(offset)
	{
		m_eState = ButtonState::NORMAL;
	}

	CButton(string name, const int* btnRgb, const int* txtRgb, Offset offset, function<void(CWindow*)> fn) : m_stName(name), m_pBtnRGB(btnRgb), m_pTxtRGB(txtRgb), m_iOffset(offset), m_fnClickCallBack(fn)
	{
		m_eState = ButtonState::NORMAL;
	}

	void DrawButton(SkCanvas& canvas, SkPaint& paint)
	{
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		SkVector radii[] = { {10, 10}, {10, 10}, {10, 10}, {10, 10} };
		rrect.setRectRadii(rrect.getBounds(), radii);
		paint.setARGB(0xFF, m_pBtnRGB[0], m_pBtnRGB[1], m_pBtnRGB[2]);
		canvas.drawRRect(rrect, paint);
		paint.setTextSize(40);
		paint.setARGB(0xFF, m_pTxtRGB[0], m_pTxtRGB[1], m_pTxtRGB[2]);
		canvas.drawString(m_stName.c_str(), m_iOffset.x + 50, m_iOffset.y + 40, paint);
	}

	bool ContainsPoint(int x, int y)
	{
		return (x > m_iOffset.x) && (x < m_iOffset.x + m_iOffset.w) && (y > m_iOffset.y) && (y < m_iOffset.y + m_iOffset.h);
	}
};
