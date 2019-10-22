#pragma once

#include <string>

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>
#include <core/SkString.h>
#include <core/SkTextBlob.h>
#include <core/SkPaint.h>
#include <core/SkRRect.h>
#include <core/SkPath.h>

#include "CWindow.hpp"
#include "CButton.hpp"
#include "CWall.hpp"
#include "CPlayer.hpp"
#include "CLava.hpp"
#include "CText.hpp"
#include "variables.h"

using std::string;

class CGameScene
{
public:
	SkBitmap m_iBmpLevel;
	vector<CWall> m_gWalls;
	CLava* m_pLava;

	CGameScene(vector<CWall> walls)
	{
		m_pLava = new CLava(100);
		m_gWalls = walls;
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
		m_iBmpLevel.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
		m_iBmpLevel.allocPixels();
		SkCanvas canvas(m_iBmpLevel);
		canvas.clear(SK_ColorBLACK);
		SkPaint paint;
		paint.setAntiAlias(true);
		m_pLava->Draw(canvas, paint, w, h);
		for (CWall wall : m_gWalls)
			wall.Draw(canvas, paint);
		player.DrawPlayer(canvas, paint);
	}
};
