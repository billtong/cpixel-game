#pragma once

#include<string>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include "entity.hpp"
#include "variables.h"
#include "CWall.hpp"

using std::string;

class CPlayer
{
public:
	string m_stName;
	const int* m_pRGB;
	Offset m_iOffset;
	const static int sm_nW = 10;
	const static int sm_nH = 20;
public:
	CPlayer()
	{
		m_stName = "Jessie";
		m_pRGB = RGBTable.white;
		m_iOffset.x = 0;
		m_iOffset.y = 0;
		m_iOffset.w = sm_nW;
		m_iOffset.h = sm_nH;
	}
	CPlayer(string name, const int* rgb, SkScalar x, SkScalar y)
	{
		m_stName = name;
		m_pRGB = rgb;
		m_iOffset.x = x;
		m_iOffset.y = y;
		m_iOffset.w = sm_nW;
		m_iOffset.h = sm_nH;
	}
	void DrawPlayer(SkCanvas& canvas, SkPaint& paint)
	{
		//printf("%d %d %d %d\n", m_iOffset.x, m_iOffset.y, m_iOffset.w, m_iOffset.h);
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		paint.setARGB(0xFF, m_pRGB[0], m_pRGB[1], m_pRGB[2]);
		canvas.drawRRect(rrect, paint);
	}

	void Move(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_LEFT:
			SDL_Log("key left pressed");
			m_iOffset.x -= 10;
			break;
		case SDLK_RIGHT:
			SDL_Log("key right pressed");
			m_iOffset.x += 10;
			break;
		case SDLK_UP:
			m_iOffset.y -= 10;
			SDL_Log("key up pressed");
			break;
		case SDLK_DOWN:
			m_iOffset.y += 10;
			SDL_Log("key down pressed");
			break;
		default:
			break;
		}
	}

	bool CollideWall(CWall wall)
	{

	}

	bool CollideBoarder(int w, int h)
	{

	}

};