#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include <core/SkString.h>
#include <core/SkTextBlob.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkPath.h>

#include "CWindow.hpp"
#include "CAccessories.hpp"
#include "CWall.hpp"
#include "CPlayer.hpp"
#include "CLava.hpp"
#include "variables.h"
#include "string"

using std::string;

class CGameScene
{
public:
	SkBitmap m_iBmpLvl;
	vector<CWall> m_gWalls;
	CLava* m_pLava;

	CGameScene(const string filepath)
	{
		m_pLava = new CLava(100);
		// should read from txt files;
		CPoint wallPointsA[6] = { {0, 400}, {200, 400}, {200, 350}, {300, 350}, {300, 430}, {0, 430} };
		CPoint wallPointsB[6] = { {350, 300}, {380, 300}, {380, 450}, {800, 450}, {800, 480}, {350, 480} };
		CPoint wallPointsC[4] = { {450, 350}, {700, 350}, {700, 400}, {450, 400} };
		CWall wallA(*new vector<CPoint>(wallPointsA, wallPointsA + 6), RGBTable.white);
		CWall wallB(*new vector<CPoint>(wallPointsB, wallPointsB + 6), RGBTable.green);
		CWall wallC(*new vector<CPoint>(wallPointsC, wallPointsC + 4), RGBTable.yellow);
		CWall wallArr[3] = { wallA, wallB, wallC };
		m_gWalls.insert(m_gWalls.end(), wallArr, wallArr + 3);
	}
	void Initialize(CPlayer& player, int(*fn)(void*), CWindow* window)
	{
		SDL_Thread* thread = SDL_CreateThread(fn, "update_game_lvl_zero", window);
		SDL_Event e;
		int threadReturnValue;
		while (!window->m_bQuit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				player.m_iCPlayerMoveStateMachine.DispatchMove(e);
				switch (e.type)
				{
				case SDL_QUIT:
					window->m_bQuit = true;
					break;
				default:
					break;
				}
			}
		}
	}
	void DrawScene(int w, int h, CPlayer player)
	{
		m_iBmpLvl.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
		m_iBmpLvl.allocPixels();
		SkCanvas canvas(m_iBmpLvl);
		canvas.clear(SK_ColorBLACK);
		SkPaint paint;
		paint.setAntiAlias(true);
		m_pLava->Draw(canvas, paint, w, h);
		for (CWall wall : m_gWalls)
			wall.Draw(canvas, paint);
		player.DrawPlayer(canvas, paint);
	}
};

class CMenuScene
{

};
