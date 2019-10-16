#include"GameMenu.h"

int UpdateMenuUI(void* data)
{
	SDL_Log("update menu ui thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = { 0, 0, window->m_iSurface->w, window->m_iSurface->h };
	while (!window->m_bQuit && !window->m_bStop)
	{
		if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		DrawMenu(rect.w, rect.h);
		window->m_iSurface = SDL_CreateRGBSurfaceFrom(g_iBmpMenu.getPixels(), rect.w, rect.h, 32, rect.w * 4,
			RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
		window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
		SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &rect);
		SDL_RenderPresent(window->m_iRenderer);
		SDL_Delay(16.6);
	}
	SDL_Log("update menu ui thread finished!");
	return 0;
}

void DrawMenu(int w, int h)
{
	g_iBmpMenu.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
	g_iBmpMenu.allocPixels();
	SkCanvas canvas(g_iBmpMenu);
	SkPaint paint;
	canvas.clear(SK_ColorBLACK);
	paint.setAntiAlias(true);
	for (CText txt : g_gTxt)
	{
		txt.DrawText(canvas, paint);
	}
	for (CButton btn : g_gBtn)
	{
		btn.DrawButton(canvas, paint);
	}
}

void InitMenu()
{
	if (g_InitWindow != nullptr)
	{
		g_InitWindow->Init("Pixel Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	CText textA = { RGBTable.red , 60, {100, 100}, "320" };
	CText textB = { RGBTable.yellow, 60, {200, 100}, "Fun" };
	CText textC = { RGBTable.blue , 60, {300, 100}, "Game" };
	g_gTxt = { textA, textB, textC };

	SDL_Thread* thread = SDL_CreateThread(UpdateMenuUI, "menu_ui_update", g_InitWindow);
	SDL_Event e;
	int threadReturnValue;
	while (g_InitWindow != nullptr && !g_InitWindow->m_bQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				g_InitWindow->m_bQuit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (g_iBtnStart.ContainsPoint(e.motion.x, e.motion.y))
				{
					SDL_Log("start btn click");
					g_InitWindow->m_bStop = true;
					SDL_WaitThread(thread, &threadReturnValue);
					g_InitWindow->m_bStop = false;
					bootstrap(g_InitWindow);
					return;
				}
				if (g_iBtnCtrl.ContainsPoint(e.motion.x, e.motion.y))
				{
					SDL_Log("control btn click");
					break;
				}
				if (g_iBtnCrdt.ContainsPoint(e.motion.x, e.motion.y))
				{
					SDL_Log("credit btn click");
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	g_InitWindow->Destroy();
}

