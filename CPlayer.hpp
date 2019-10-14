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
		Offset temp = { sm_nW, sm_nH, 0, 0 };
		m_iOffset = temp;
	}
	CPlayer(string name, const int* rgb, SkScalar x, SkScalar y)
	{
		m_stName = name;
		m_pRGB = rgb;
		Offset temp = { sm_nW, sm_nH, x, y};
		m_iOffset = temp;
	}

	void DrawPlayer(SkCanvas& canvas, SkPaint& paint)
	{
		//printf("%d %d %d %d\n", m_iOffset.x, m_iOffset.y, m_iOffset.w, m_iOffset.h);
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		paint.setARGB(0xFF, m_pRGB[0], m_pRGB[1], m_pRGB[2]);
		canvas.drawRRect(rrect, paint);
	}

	void Move(SDL_Keycode key, SDL_Surface *surface, vector<CWall> walls)
	{
		SkScalar tempX = m_iOffset.x;
		SkScalar tempY = m_iOffset.y;
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
			m_iOffset.y += 2;
			SDL_Log("key down pressed");
			break;
		default:
			break;
		}
		if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
		{
			m_iOffset.x = tempX;
			m_iOffset.y = tempY;
		}
	}

	bool CollideWall(vector<CWall> walls)
	{
		Point p1(m_iOffset.x, m_iOffset.y);
		Point p2(m_iOffset.x + m_iOffset.w, m_iOffset.y);
		Point p3(m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h);
		Point p4(m_iOffset.x, m_iOffset.y + m_iOffset.h);
		Point points[4] = { p1, p2, p3, p4 };	// clockwise from left top point.
		for (CWall wall : walls)
		{
			for (Point p : points)
			{
				if (p.IncludedByPoints(wall.m_gPoints))
					return true;
			}
		}
		return false;
	}

	bool CollideBoarder(int w, int h)
	{
		return m_iOffset.x < 0 || m_iOffset.x > (w - m_iOffset.w) || m_iOffset.y < 0 || m_iOffset.y > (h - m_iOffset.h);
	}

};