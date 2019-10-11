#include"ui.h"
#include<ctime>

int UpdateMenuUI(void* data)
{
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = {0, 0, window->m_iSurface->w, window->m_iSurface->h};
	int i = 0;
	while (!window->m_bQuit && !window->m_bStop)
	{
		SDL_Log("update menu ui thread at %d", i);
		if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		g_iBmpMenu = DrawMenu(rect.w, rect.h);
		window->m_iSurface = SDL_CreateRGBSurfaceFrom(g_iBmpMenu.getPixels(), rect.w, rect.h, 32, rect.w * 4,
			RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
		window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
		SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &rect);
		SDL_RenderPresent(window->m_iRenderer);
		SDL_Delay(16.6);
		i++;
	}
	return 0;
}

SkBitmap DrawMenu(int w, int h)
{
	g_iBmpMenu.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
	g_iBmpMenu.allocPixels();
	SkCanvas canvas(g_iBmpMenu);
	SkPaint paint;
	canvas.clear(SK_ColorBLACK);
	paint.setAntiAlias(true);
	paint.setTextSize(60);
	paint.setARGB(0xFF, RGBTable.red[0], RGBTable.red[1], RGBTable.red[2]);
	canvas.drawString("320", 100, 100, paint);
	paint.setARGB(0xFF, RGBTable.yellow[0], RGBTable.yellow[1], RGBTable.yellow[2]);
	canvas.drawString("Fun", 200, 100, paint);
	paint.setARGB(0xFF, RGBTable.blue[0], RGBTable.blue[1], RGBTable.blue[2]);
	canvas.drawString("Game", 300, 100, paint);
	g_iBtnStart.DrawButton(canvas, paint);
	g_iBtnCtrl.DrawButton(canvas, paint);
	g_iBtnCrdt.DrawButton(canvas, paint);
	return  g_iBmpMenu;
}
