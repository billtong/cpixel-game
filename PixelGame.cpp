#include"GameMenu.h"

int main(int args, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	InitMenu();
	SDL_Quit();
	return 0;
}