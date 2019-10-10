/*
	Author: Bill Tong, Nalsen Yang
*/

#include "stdafx.h"

int main(int args, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	InitUI();
	SDL_Quit();
	return 0;
}