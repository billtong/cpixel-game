#include"GameMenu.h"

int UpdateMenuUI(void* data)
{
	SDL_Log("update menu ui thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = { 0, 0, window->m_iSurface->w, window->m_iSurface->h };
	while (!window->m_bQuit && !window->m_bStop)
	{
		// 0xc0000005 Access violation
		//if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		//if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		g_iMenuScene.Draw(window->m_iSurface->w, window->m_iSurface->h);
		window->m_iSurface = SDL_CreateRGBSurfaceFrom(g_iMenuScene.m_iBmpMenu.getPixels(), rect.w, rect.h, 32, rect.w * 4,
			RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
		window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
		SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &rect);
		SDL_RenderPresent(window->m_iRenderer);
		SDL_Delay(16.6);
	}
	SDL_Log("update menu ui thread finished!");
	return 0;
}

void InitMenu()
{
	if (g_iWindow != nullptr)
		g_iWindow->Init("Pixel Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	CButton btnA("Start Game", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 250 }, bootstrap);
	CButton btnB("Controls", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 350 });
	CButton btnC("Credits", RGBTable.yellow, RGBTable.navy, { 350, 50, 100, 450 });
	vector<CButton> btns = { btnA, btnB, btnC };
	CText textA = { RGBTable.red , 60, {100, 100}, "320" };
	CText textB = { RGBTable.yellow, 60, {200, 100}, "Fun" };
	CText textC = { RGBTable.blue , 60, {300, 100}, "Game" };
	vector<CText> txts = { textA, textB, textC };
	g_iMenuScene = CMenuScene(btns, txts);
	g_iMenuScene.Initialize(UpdateMenuUI, g_iWindow);
	g_iWindow->Destroy();
}

