#include "GameLvlZero.h"

int UpdateGameLvlZeroUI(void* data)
{
	SDL_Log("lvl zero update ui thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = { 0, 0, window->m_iSurface->w, window->m_iSurface->h };
	while (!window->m_bQuit && !window->m_bStop)
	{
		if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		g_iBmpLvlZero = DrawGameLvlZero(rect.w, rect.h);
		window->m_iSurface = SDL_CreateRGBSurfaceFrom(g_iBmpLvlZero.getPixels(), rect.w, rect.h, 32, rect.w * 4, RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
		window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
		SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &rect);
		SDL_RenderPresent(window->m_iRenderer);
		SDL_Delay(16.6);
	}
	SDL_Log("lvl zero update ui thread finished!");
	return 0;
}

SkBitmap DrawGameLvlZero(int w, int h)
{
	g_iBmpLvlZero.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
	g_iBmpLvlZero.allocPixels();
	SkCanvas canvas(g_iBmpLvlZero);
	canvas.clear(SK_ColorBLACK);
	SkPaint paint;
	paint.setAntiAlias(true);
	SkPath path;
	path.moveTo(0, 400);
	path.lineTo(200, 400);
	path.lineTo(200, 430);
	path.lineTo(0, 430);
	path.close();
	paint.setStyle(SkPaint::kStrokeAndFill_Style);
	paint.setARGB(0xFF, RGBTable.white[0], RGBTable.white[1], RGBTable.white[2]);
	canvas.drawPath(path, paint);
	g_iPlayer.DrawPlayer(canvas, paint);
	return g_iBmpLvlZero;
}

int UpdateGForce(void* data)
{
	SDL_Log("lvl zero upgrade GForce thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	while (!window->m_bQuit && !window->m_bStop)
	{
		g_iPlayer.m_iOffset.y++;
		SDL_Delay(20);
	}
	SDL_Log("lvl zero upgrade GForce thread finished!");
	return 0;
}

void InitGameLvlZero(CWindow* window)
{
	SDL_Thread* thread1 = SDL_CreateThread(UpdateGameLvlZeroUI, "update_game_lvl_zero", window);
	//SDL_Thread* thread2= SDL_CreateThread(UpdateGForce, "update_player_fall", window);
	SDL_Event e;
	int threadReturnValue;
	while (!window->m_bQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			SDL_Keycode key = e.key.keysym.sym;
			switch (e.type)
			{
			case SDL_QUIT:
				window->m_bQuit = true;
				break;
			case SDL_KEYDOWN:
				if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
				{
					g_iPlayer.Move(key);
				}
				break;
			default:
				break;
			}
		}
	}
	window->Destroy();
}