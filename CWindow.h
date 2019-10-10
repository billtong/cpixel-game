/*
	Author: Bill Tong
*/

#pragma once
#ifdef _WIN32

#pragma warning(disable:4996)
#include <SDL.h>
#include <SDL_thread.h>
#else
#include <SDL2/SDL.h>
#endif

class CWindow
{
public:
	SDL_Window* m_iWindow;
	SDL_Surface* m_iSurface;
	SDL_Renderer* m_iRenderer;
	SDL_Texture* m_iTexture;
	SDL_Rect m_iRect;
	bool m_bQuit;

public:
	void Init(const char* name, int width, int height);
	void Destroy();
};

