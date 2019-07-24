#include "ImageLib.h"
#include "MyGfx.h"

void TestImageLib_Load() 
{
	auto lib = ImageLib();
	lib.Load("LoginInterface.wix");
}

void TestImageLib_LoadImage()
{
	auto lib = ImageLib();
	lib.Load("LoginInterface.wix");
	Image* img = lib.LoadImage(0);
	delete img;
}

void TestMyGfxCreateSpriteFromImage()
{
	auto lib = ImageLib();
	lib.Load("LoginInterface.wix");
	Image* img = lib.LoadImage(0);
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	window = SDL_CreateWindow("TestWIL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, img->Width, img->Height, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);
	auto sprite = MyGfx::CreateSpriteFromImage(img);
	SDL_BlitSurface(sprite->Surface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	SDL_FreeSurface(sprite->Surface);
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
}