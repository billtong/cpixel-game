#include "stdafx.h"

int main(int args, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	g_InitWindow->Init("Pixel Game",WINDOW_WIDTH, WINDOW_HEIGHT);
	InitMenu();
	SDL_Quit();
	return 0;
}