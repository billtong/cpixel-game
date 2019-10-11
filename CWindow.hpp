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
	bool m_bQuit;
	bool m_bStop;

public:
	void Init(const char* name, int width, int height) {
		m_bQuit = false;
		m_bStop = false;
		m_iWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		m_iRenderer = SDL_CreateRenderer(m_iWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_RenderClear(m_iRenderer);
		m_iSurface = SDL_GetWindowSurface(m_iWindow);
	}
	void Destroy() {
		if (m_iSurface != NULL) SDL_FreeSurface(m_iSurface);
		if (m_iTexture != NULL) SDL_DestroyTexture(m_iTexture);
		if (m_iRenderer != NULL) SDL_DestroyRenderer(m_iRenderer);
		SDL_DestroyWindow(m_iWindow);
	}
};