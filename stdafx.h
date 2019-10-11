#ifndef STDAFX_H
#define STDAFX_H

#include"ui.h"
#include"variables.h"

void InitMenu()
{
	SDL_Thread* thread = SDL_CreateThread(UpdateMenuUI, "menu_ui_update", (CWindow*)g_InitWindow);
	SDL_Event e;
	int threadReturnValue;
	while (!g_InitWindow->m_bQuit) 
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
					InitGameLevelZero();
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

void InitGameLevelZero()
{

}

#endif // !STDAFX_H
