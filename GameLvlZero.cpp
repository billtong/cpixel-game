#include "GameLvlZero.h"

int UpdateGameLvlZeroUI(void* data)
{
	SDL_Log("lvl zero update ui thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = { 0, 0, window->m_iSurface->w, window->m_iSurface->h };
	int hopCounter = 0;
	while (!window->m_bQuit && !window->m_bStop)
	{
		if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
		if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
		switch (g_iPlayer.m_eState)
		{
		case PlayerState::stay:
			g_iPlayer.Fall(window->m_iSurface, g_gWalls);
			break;
		case PlayerState::walk:
			g_iPlayer.Walk(false, window->m_iSurface, g_gWalls);
			break;
		case PlayerState::back:
			g_iPlayer.Walk(true, window->m_iSurface, g_gWalls);
			break;
		case PlayerState::hop:
			g_iPlayer.Hop(window->m_iSurface, g_gWalls, hopCounter);
			break;
		case PlayerState::walkhop:
			g_iPlayer.Hop(window->m_iSurface, g_gWalls, hopCounter);
			g_iPlayer.Walk(false, window->m_iSurface, g_gWalls);
			break;
		case PlayerState::backhop:
			g_iPlayer.Hop(window->m_iSurface, g_gWalls, hopCounter);
			g_iPlayer.Walk(true, window->m_iSurface, g_gWalls);
			break;
		default:
			g_iPlayer.Fall(window->m_iSurface, g_gWalls);
			break;
		}
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
	
	for (CWall wall : g_gWalls)
	{
		wall.Draw(canvas, paint);
	}
	g_iPlayer.DrawPlayer(canvas, paint);
	return g_iBmpLvlZero;
}

void InitGameLvlZero(CWindow* window)
{
	// inital walls
	Point wallPoints[6] = { {0, 400}, {200, 400}, {200, 350}, {300, 350}, {300, 430}, {0, 430} };
	vector<Point> points(wallPoints, wallPoints+6);
	CWall walla(points, RGBTable.white);
	g_gWalls.push_back(walla);
	SDL_Thread* thread = SDL_CreateThread(UpdateGameLvlZeroUI, "update_game_lvl_zero", window);
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

				if (g_iPlayer.m_eState == PlayerState::hop)
				{
					switch (key)
					{
					case SDLK_LEFT:
						g_iPlayer.m_eState = PlayerState::backhop;
						break;
					case SDLK_RIGHT:
						g_iPlayer.m_eState = PlayerState::walkhop;
						break;
					default:
						break;
					}
				}
				else {
					switch (key)
					{
					case SDLK_LEFT:
						g_iPlayer.m_eState = PlayerState::back;
						break;
					case SDLK_RIGHT:
						g_iPlayer.m_eState = PlayerState::walk;
						break;
					case SDLK_UP:
						g_iPlayer.m_eState = PlayerState::hop;
						break;
					default:
						g_iPlayer.m_eState = PlayerState::stay;
						break;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	window->Destroy();
}
