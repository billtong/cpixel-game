#pragma once

#include<string>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include "entity.hpp"
#include "CWall.hpp"
#include "CLava.hpp"
#include "variables.h"

using std::string;
using std::to_string;

enum class PlayerState { stay, walk, back, hop, walkhop, backhop };
enum class PlayerSide {left, right, up, down};

class CPlayer
{
public:
	int m_nBlood;
	const int* m_pRGB;
	const static int sm_nW = 10;
	const static int sm_nH = 20;
	const static int sm_hopHeight = 30;
	string m_stName;
	Offset m_iOffset;
	PlayerState m_eState;

public:
	CPlayer(int blood,string name, const int* rgb, SkScalar x, SkScalar y)
	{
		m_nBlood = blood;
		m_pRGB = rgb;
		m_stName = name;
		Offset temp = { sm_nW, sm_nH, x, y };
		m_iOffset = temp;
		m_eState = PlayerState::stay;
	}

	void DrawPlayer(SkCanvas& canvas, SkPaint& paint)
	{
		//printf("%d %d %d %d\n", m_iOffset.x, m_iOffset.y, m_iOffset.w, m_iOffset.h);
		paint.setARGB(0xFF, m_pRGB[0], m_pRGB[1], m_pRGB[2]);
		paint.setTextSize(20);
		string life = to_string(m_nBlood);
		canvas.drawString(life.c_str(), 30, 30, paint);
		SkRRect rrect = SkRRect::MakeRect({ m_iOffset.x, m_iOffset.y, m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h });
		canvas.drawRRect(rrect, paint);
	}

	void Walk(bool isBack, SDL_Surface* surface, vector<CWall> walls)
	{
		for (int i = 1; i <= 6; i++)
		{
			SkScalar tempX = m_iOffset.x;
			m_iOffset.x = isBack ? m_iOffset.x - 1 : m_iOffset.x + 1;
			if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::left) || CollideWall(walls, PlayerSide::right))
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
				SkScalar tempY = m_iOffset.y;
				m_iOffset.y = counter < (sm_hopHeight / 2) ? m_iOffset.y - 1 : m_iOffset.y + 1;
				if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::up) || CollideWall(walls, PlayerSide::down))
				{
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
					if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::left))
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
					if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::right))
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
			if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::down) || CollideWall(walls, PlayerSide::left) || CollideWall(walls, PlayerSide::right))
			{
				m_iOffset.y = tempY;
				break;
			}
		}
	}

	bool CollideWall(vector<CWall> walls, PlayerSide side)
	{
		// clockwise from left top point.
		Point p1(m_iOffset.x, m_iOffset.y);
		Point p2(m_iOffset.x + m_iOffset.w, m_iOffset.y);
		Point p3(m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h);
		Point p4(m_iOffset.x, m_iOffset.y + m_iOffset.h);
		switch (side)
		{
		case PlayerSide::left:
			for (CWall wall : walls)
			{
				if (Point::TwoPointsIntersectPoints(p1, p4, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::right:
			for (CWall wall : walls)
			{
				if (Point::TwoPointsIntersectPoints(p2, p3, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::up:
			for (CWall wall : walls)
			{
				if (Point::TwoPointsIntersectPoints(p1, p2, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::down:
			for (CWall wall : walls)
			{
				if (Point::TwoPointsIntersectPoints(p3, p4, wall.m_gPoints))
					return true;
			}
			break;
		default:
			return false;
			break;
		}
		return false;
	}

	bool CollideBoarder(int w, int h)
	{
		return m_iOffset.x < 0 || m_iOffset.x > (w - m_iOffset.w) || m_iOffset.y < 0 || m_iOffset.y > (h - m_iOffset.h);
	}

	bool FallIntoLava(CLava lava, int h)
	{
		return m_iOffset.y >= h - lava.m_nHeight;
	}
};