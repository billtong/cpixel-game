#include "CWindow.h"

void CWindow::Init(const char* name, int width, int height)
{
	m_bQuit = false;
	m_iWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	m_iRenderer = SDL_CreateRenderer(m_iWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(m_iRenderer);
	m_iSurface = SDL_GetWindowSurface(m_iWindow);
	SDL_Rect src = { 0, 0, m_iSurface->w, m_iSurface->h };
	m_iRect = src;
}

void CWindow::Destroy()
{
	if (m_iSurface != NULL) SDL_FreeSurface(m_iSurface);
	if (m_iTexture != NULL) SDL_DestroyTexture(m_iTexture);
	if (m_iRenderer != NULL) SDL_DestroyRenderer(m_iRenderer);
	SDL_DestroyWindow(m_iWindow);
}
