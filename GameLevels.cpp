#include "GameLevels.h"

void bootstrap(CWindow* window)
{
	g_iLvlZero.Initialize(g_iPlayer, UpdateGameLevelZeroUI, window);
}

int UpdateGameLevelZeroUI(void* data)
{
	SDL_Log("lvl zero update ui thread started!");
	CWindow* window = static_cast<CWindow*>(data);
	SDL_Rect rect = { 0, 0, window->m_iSurface->w, window->m_iSurface->h };
	int hopCounter = 0;
	while (!window->m_bQuit && !window->m_bStop)
	{
		if (g_iPlayer.FallIntoLava(*g_iLvlZero.m_pLava, window->m_iSurface->h))
		{
			if (g_iPlayer.m_nBlood > 0)
			{
				g_iPlayer.m_nBlood--;
				g_iPlayer.m_iOffset = { CPlayer::sm_nW, CPlayer::sm_nH, 0, 350 };
			}
			else {
				SDL_Log("You are dead!");
				break;
			}
		}
		else {
			if (window->m_iSurface != NULL) SDL_FreeSurface(window->m_iSurface);
			if (window->m_iTexture != NULL) SDL_DestroyTexture(window->m_iTexture);
			g_iLvlZero.DrawScene(rect.w, rect.h, g_iPlayer);
			window->m_iSurface = SDL_CreateRGBSurfaceFrom(g_iLvlZero.m_iBmpLvl.getPixels(), rect.w, rect.h, 32, rect.w * 4, RGBA.rmask, RGBA.gmask, RGBA.bmask, RGBA.amask);
			window->m_iTexture = SDL_CreateTextureFromSurface(window->m_iRenderer, window->m_iSurface);
			SDL_RenderCopy(window->m_iRenderer, window->m_iTexture, NULL, &rect);
			SDL_RenderPresent(window->m_iRenderer);

			g_iPlayer.m_iCPlayerMoveStateMachine.ExecuteMove(window->m_iSurface, g_iLvlZero.m_gWalls);
		}
		SDL_Delay(16.6);
	}
	SDL_Log("lvl zero update ui thread finished!");
	return 0;
}
