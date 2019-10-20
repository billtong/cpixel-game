#pragma once

#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkPaint.h>

#include "CWindow.hpp"
#include "CText.hpp"
#include "CButton.hpp"

using std::vector;

class CMenuScene
{
public:
	SkBitmap m_iBmpMenu;
	vector<CButton> m_gBtn;
	vector<CText> m_gTxt;
	CMenuScene() {}
	CMenuScene(vector<CButton> btns, vector<CText> txts) : m_gBtn(btns), m_gTxt(txts) {}
	void Initialize(int(*fn)(void*), CWindow* window)
	{
		SDL_Thread* thread = SDL_CreateThread(fn, "menu_ui_update", window);
		SDL_Event e;
		int threadReturnValue;
		while (window != nullptr && !window->m_bQuit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					window->m_bQuit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (CButton btn : m_gBtn)
					{
						if (btn.ContainsPoint(e.motion.x, e.motion.y))
						{
							SDL_Log("%s down", btn.m_stName);
							btn.m_eState = ButtonState::HOVER;
							break;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					for (CButton btn : m_gBtn)
					{
						if (btn.ContainsPoint(e.motion.x, e.motion.y))
						{
							SDL_Log("%s up %s", btn.m_stName, ButtonStateName[static_cast<int>(btn.m_eState)]);
							window->m_bStop = true;
							SDL_WaitThread(thread, &threadReturnValue);
							window->m_bStop = false;
							btn.m_fnClickCallBack(window);
							break;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}

	void Draw(int w, int h)
	{
		m_iBmpMenu.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
		m_iBmpMenu.allocPixels();
		SkCanvas canvas(m_iBmpMenu);
		SkPaint paint;
		canvas.clear(SK_ColorBLACK);
		paint.setAntiAlias(true);
		for (CText txt : m_gTxt)
			txt.DrawText(canvas, paint);
		for (CButton btn : m_gBtn)
			btn.DrawButton(canvas, paint);
	}
};