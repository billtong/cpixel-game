#include "GameLvlZero.h"

int UpdateGameLvlZero(void* data)
{
	CWindow* window = static_cast<CWindow*>(data);
	while (!window->m_bQuit && !window->m_bStop)
	{
		SDL_Log("lvl zero");
		SDL_Delay(10);
	}
	return 0;
}

SkBitmap DrawGameLvlZero(int w, int h)
{
	return SkBitmap();
}

void InitGameLvlZero(CWindow* window)
{
	SDL_Thread* thread = SDL_CreateThread(UpdateGameLvlZero, "update_game_lvl_zero", window);
	SDL_Event e;
	int threadReturnValue;
	while (!window->m_bQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
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
	window->Destroy();
}
