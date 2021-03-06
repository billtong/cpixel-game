#pragma once

#include<string>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkString.h>

#include "CPoint.hpp"
#include "CWall.hpp"
#include "CLava.hpp"
#include "variables.h"

#define METHOD_PROLOGUE(theClass, localClass) theClass* pThis = ((theClass*)((char*)(this) - offsetof(theClass, m_i##localClass)));

using std::vector;
using std::string;
using std::to_string;

enum class PlayerMoveState { stay, walk, back, hop, walkhop, backhop, fall, walkfall, backfall };
const static char* PlayerMoveStateName[9] = { "stay", "walk", "back", "hop", "walkhop", "backhop", "fall", "walkfall", "backfall" };	/* for debuging only */
enum class PlayerSide { left, right, up, down };

class CPlayer
{
public:
	int m_nBlood;
	const int* m_pRGB;
	const static int sm_nW = 10;
	const static int sm_nH = 20;
	const static int sm_hopHeight = 30;
	int sm_nWalkSpeed;
	int sm_nHopSpeed;
	int sm_nFallSpeed;
	string m_stName;
	Offset m_iOffset;
	PlayerMoveState m_eState;
	
	CPlayer(int blood, string name, const int* rgb, SkScalar x, SkScalar y)
	{
		m_nBlood = blood;
		m_pRGB = rgb;
		m_stName = name;
		Offset temp = { sm_nW, sm_nH, x, y };
		m_iOffset = temp;
		m_eState = PlayerMoveState::fall;
		sm_nWalkSpeed = 6;
		sm_nHopSpeed = 6;
		sm_nFallSpeed = 8;
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
		for (int i = 1; i <= sm_nWalkSpeed; i++)
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
			m_eState = PlayerMoveState::fall;
		}
		else {
			if (m_eState == PlayerMoveState::backhop || m_eState == PlayerMoveState::walkhop)
			{
				Walk(m_eState == PlayerMoveState::backhop, surface, walls);
			}
			for (int i = 1; i <= sm_nFallSpeed; i++)
			{
				SkScalar tempY = m_iOffset.y;
				m_iOffset.y = counter < (sm_hopHeight / 2) ? m_iOffset.y - 1 : m_iOffset.y + 1;
				if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::up) || CollideWall(walls, PlayerSide::down))
				{
					m_iOffset.y = tempY;
					counter = 0;
					m_eState = PlayerMoveState::fall;
					break;
				}
			}
			counter++;
		}
	}

	void Fall(SDL_Surface* surface, vector<CWall> walls)
	{
		SkScalar temp = m_iOffset.y;
		PlayerMoveState originState = m_eState;

		if (m_eState == PlayerMoveState::backfall || m_eState == PlayerMoveState::walkfall)
		{
			Walk(m_eState == PlayerMoveState::backfall, surface, walls);
		}
		for (int i = 1; i <= sm_nFallSpeed; i++)
		{
			SkScalar tempY = m_iOffset.y;
			m_iOffset.y++;
			if (CollideBoarder(surface->w, surface->h) || CollideWall(walls, PlayerSide::down) || CollideWall(walls, PlayerSide::left) || CollideWall(walls, PlayerSide::right))
			{
				m_iOffset.y = tempY;
				m_eState = PlayerMoveState::stay;
				break;
			}
		}

		if (temp != m_iOffset.y)
		{
			if (originState == PlayerMoveState::walk)
			{
				m_eState = PlayerMoveState::walkfall;
			}
			else if (originState == PlayerMoveState::back)
			{
				m_eState = PlayerMoveState::backfall;
			}
		}
		else if (originState != PlayerMoveState::fall)
		{
			m_eState = originState;
		}
	}

	bool CollideWall(vector<CWall> walls, PlayerSide side)
	{
		// clockwise from left top point.
		CPoint p1(m_iOffset.x, m_iOffset.y);
		CPoint p2(m_iOffset.x + m_iOffset.w, m_iOffset.y);
		CPoint p3(m_iOffset.x + m_iOffset.w, m_iOffset.y + m_iOffset.h);
		CPoint p4(m_iOffset.x, m_iOffset.y + m_iOffset.h);
		switch (side)
		{
		case PlayerSide::left:
			for (CWall wall : walls)
			{
				if (CPoint::TwoPointsIntersectPoints(p1, p4, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::right:
			for (CWall wall : walls)
			{
				if (CPoint::TwoPointsIntersectPoints(p2, p3, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::up:
			for (CWall wall : walls)
			{
				if (CPoint::TwoPointsIntersectPoints(p1, p2, wall.m_gPoints))
					return true;
			}
			break;
		case PlayerSide::down:
			for (CWall wall : walls)
			{
				if (CPoint::TwoPointsIntersectPoints(p3, p4, wall.m_gPoints))
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
		return m_iOffset.x < 0 || m_iOffset.x >(w - m_iOffset.w) || m_iOffset.y < 0 || m_iOffset.y >(h - m_iOffset.h);
	}

	bool FallIntoLava(CLava lava, int h)
	{
		return m_iOffset.y >= h - lava.m_nHeight;
	}

	class CPlayerMoveStateMachine
	{
	public:
		int m_nHopCounter;

		CPlayerMoveStateMachine()
		{
			m_nHopCounter = 0;
		}
		void DispatchMove(SDL_Event e)
		{
			METHOD_PROLOGUE(CPlayer, CPlayerMoveStateMachine);
			SDL_Keycode key = e.key.keysym.sym;
			switch (e.type)
			{
			case SDL_KEYDOWN:
				if (pThis->m_eState == PlayerMoveState::hop || pThis->m_eState == PlayerMoveState::walkhop || pThis->m_eState == PlayerMoveState::backhop)
				{
					switch (key)
					{
					case SDLK_LEFT:
						pThis->m_eState = PlayerMoveState::backhop;
						break;
					case SDLK_RIGHT:
						pThis->m_eState = PlayerMoveState::walkhop;
						break;
					default:
						break;
					}
				}
				else {
					switch (key)
					{
					case SDLK_UP:
						if (pThis->m_eState != PlayerMoveState::fall && pThis->m_eState != PlayerMoveState::walkfall && pThis->m_eState != PlayerMoveState::backfall)
						{
							if (pThis->m_eState == PlayerMoveState::walk)
							{
								pThis->m_eState = PlayerMoveState::walkhop;
							}
							else if(pThis->m_eState == PlayerMoveState::back)
							{
								pThis->m_eState = PlayerMoveState::backhop;
							}
							else
							{
								pThis->m_eState = PlayerMoveState::hop;
							}
						}
						break;
					case SDLK_LEFT:
						pThis->m_eState = PlayerMoveState::back;
						break;
					case SDLK_RIGHT:
						pThis->m_eState = PlayerMoveState::walk;
						break;
					default:
						pThis->m_eState = PlayerMoveState::fall;
						break;
					}
				}
				break;
			case SDL_KEYUP:
				//SDL_Log("key up");
				if (pThis->m_eState == PlayerMoveState::hop || pThis->m_eState == PlayerMoveState::walkhop || pThis->m_eState == PlayerMoveState::backhop)
					pThis->m_eState = PlayerMoveState::hop;
				else
					pThis->m_eState = PlayerMoveState::fall;
				break;
			default:
				break;
			}
		}

		void ExecuteMove(SDL_Surface *surface, vector<CWall> walls)
		{
			METHOD_PROLOGUE(CPlayer, CPlayerMoveStateMachine);
			SDL_Log("%s", PlayerMoveStateName[static_cast<int>(pThis->m_eState)]);
			if (pThis->m_eState == PlayerMoveState::hop || pThis->m_eState == PlayerMoveState::walkhop || pThis->m_eState == PlayerMoveState::backhop)
				pThis->Hop(surface, walls, m_nHopCounter);
			else if (pThis->m_eState == PlayerMoveState::walk || pThis->m_eState == PlayerMoveState::back)
			{
				pThis->Walk(pThis->m_eState == PlayerMoveState::back, surface, walls);
				pThis->Fall(surface, walls);
			}
			else
				pThis->Fall(surface, walls);
		}
	}m_iCPlayerMoveStateMachine;
};

