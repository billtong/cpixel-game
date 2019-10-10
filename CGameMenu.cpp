/*
	Author: Bill Tong
*/

#include"CSkiaUI.h"

int UpdateMenu(void* data)
{
	CWindow* window = static_cast<CWindow*>(data);
	while (!window->m_bQuit) {
		if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		bitmap = DrawMenu(window->m_iRect.w, window->m_iRect.h);
		window->m_iSurface = SDL_CreateRGBSurfaceFrom(bitmap.getPixels(), window->m_iRect.w, window->m_iRect.h, 32, window->m_iRect.w * 4, 
			RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
		window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
		SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &(window->m_iRect));
		SDL_RenderPresent(window->m_iRenderer);
		SDL_Delay(16.6);
	}
	return 0;
}

SkBitmap DrawMenu(int w, int h)
{
	bitmap.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
	bitmap.allocPixels();
	SkCanvas canvas(bitmap);
	SkPaint paint;
	canvas.clear(SK_ColorBLACK);
	paint.setAntiAlias(true);
	paint.setTextSize(60);
	paint.setARGB(0xFF, RGBTable.red[0], RGBTable.red[1], RGBTable.red[2]);
	canvas.drawString("320", 100, 100, paint);
	paint.setARGB(0xFF, 0xFF, 0xFF, 0xFF);
	paint.setARGB(0xFF, RGBTable.yellow[0], RGBTable.yellow[1], RGBTable.yellow[2]);
	canvas.drawString("Fun", 200, 100, paint);
	paint.setARGB(0xFF, RGBTable.blue[0], RGBTable.blue[1], RGBTable.blue[2]);
	canvas.drawString("Game", 300, 100, paint);
	return bitmap;
}
