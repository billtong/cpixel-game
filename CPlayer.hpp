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

enum class PlayerState { stay, walk, back, hop, walkhop, backhop };

class CPlayer
{
public:
	string m_stName;
	const int* m_pRGB;
	Offset m_iOffset;
	const static int sm_nW = 10;
	const static int sm_nH = 20;
	const static int sm_hopHeight = 30;
	PlayerState m_eState;

public:
	CPlayer()
	{
		m_stName = "Jessie";
		m_pRGB = RGBTable.red;
		Offset temp = { sm_nW, sm_nH, 0, 0 };
		m_iOffset = temp;
		m_eState = PlayerState::stay;
	}
	CPlayer(string name, const int* rgb, SkScalar x, SkScalar y) : CPlayer()
	{
		m_stName = name;
		m_pRGB = rgb;
		Offset temp = { sm_nW, sm_nH, x, y };
		m_iOffset = temp;
	}

	void DrawPlayer(SkCanvas& canvas, SkPaint& paint)
	{
		//printf("%d %d %d %d\n", m_iOffset.x, m_iOffset.y, m_iOffset.w, m_iOffset.h);
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		paint.setARGB(0xFF, m_pRGB[0], m_pRGB[1], m_pRGB[2]);
		canvas.drawRRect(rrect, paint);
	}

	void Walk(bool isBack, SDL_Surface* surface, vector<CWall> walls)
	{
		for (int i = 1; i <= 6; i++)
		{
			SkScalar tempX = m_iOffset.x;
			m_iOffset.x = isBack ? m_iOffset.x - 1 : m_iOffset.x + 1;
			if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
			{
				m_iOffset.x = tempX;
				break;
			}
		}
	}

	void Hop(SDL_Surface* surface, vector<CWall> walls, int& counter)
	{
		
		if (counter == sm_hopHeight)
		{
			counter = 0;
			m_eState = PlayerState::stay;
		}
		else {
			for (int i = 1; i <= 8; i++)
			{
				SkScalar tempX = m_iOffset.x;
				SkScalar tempY = m_iOffset.y;
				m_iOffset.y = counter < (sm_hopHeight / 2) ? m_iOffset.y - 1 : m_iOffset.y + 1;
				if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
				{
					m_iOffset.x = tempX;
					m_iOffset.y = tempY;
					break;
				}
			}

			if (m_eState == PlayerState::backhop)
			{
				for (int i = 1; i <= 6; i++)
				{
					SkScalar tempX = m_iOffset.x;
					m_iOffset.x--;
					if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
					{
						m_iOffset.x = tempX;
						break;
					}
				}
			}
			if (m_eState == PlayerState::walkhop)
			{
				for (int i = 1; i <= 6; i++)
				{
					SkScalar tempX = m_iOffset.x;
					m_iOffset.x++;
					if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
					{
						m_iOffset.x = tempX;
						break;
					}
				}
			}
			counter++;
		}
	}

	void Fall(SDL_Surface* surface, vector<CWall> walls)
	{
		for (int i = 1; i <= 8; i++)
		{
			SkScalar tempY = m_iOffset.y;
			m_iOffset.y ++;
			if (CollideBoarder(surface->w, surface->h) || CollideWall(walls))
			{
				m_iOffset.y = tempY;
				break;
			}
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
			int i = 0;
			for (Point p : points)
			{
				if (p.IncludedByPoints(wall.m_gPoints)) {
					i++;
				}
			}
			if (i >= 2)
			{
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