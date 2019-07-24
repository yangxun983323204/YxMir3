#include "SDLInc.h"
#include <stdio.h>
#include "Test.h"

int main(int argc, char* argv[])
{
	Test();
	return 0;
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,480, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			SDL_Surface *img = SDL_LoadBMP("test.bmp");
			if (img == nullptr)
			{
				printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
			}
			SDL_BlitSurface(img, NULL, screenSurface, NULL);

			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}