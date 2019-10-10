/*
	Author: Bill Tong, Nalsen Yang
*/

#ifndef STDAFX_H
#define STDAFX_H

#include"CWindow.h"
#include"CSkiaUI.h"
#include"GlobalVar.h"

CWindow *menuWindow = new CWindow;

void InitUI()
{
	menuWindow->Init("Pixel Game",WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Thread* thread = SDL_CreateThread(UpdateMenu, "update", (CWindow*)menuWindow);
	SDL_Event e;
	while (!menuWindow->m_bQuit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				menuWindow->m_bQuit = true;
		}
	}
	menuWindow->Destroy();
}

#endif // !STDAFX_H
