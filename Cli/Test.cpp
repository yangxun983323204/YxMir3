#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"
#include "WILIndex.h"

void TestImageLib_Load() 
{
	auto lib = ImageLib();
	lib.Load("Data/LoginInterface.wix");
}

void TestImageLib_LoadImage()
{
	auto lib = ImageLib();
	lib.Load("Data/LoginInterface.wix");
	Image* img = lib.LoadImage(0);
	delete img;
}

void TestMyGfxCreateSpriteFromImage()
{
	auto lib = ImageLib();
	lib.Load("Data/LoginInterface.wix");
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

void TestMapLoad()
{
	Map map;
	map.Load("Map/D008.map");
	printf("map w:%d,h:%d", map.w(), map.h());
}
void TestDrawMapRect() 
{
	// 还有问题，先不研究了
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	window = SDL_CreateWindow("TestWIL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	MyGfx *gfx = new MyGfx(window);

	Map map;
	map.Load("Map/D008.map");
	int offsetX = 0;
	int offsetY = 0;
	for (size_t i = 0; i < 18; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			auto tile = map.TileAt(i + offsetY, j + offsetX);
			int fileIdx = tile.FileIndex;
			ImageLib::ExFileIdx(fileIdx);
			if ((fileIdx % 14) > 2)
				continue;
			if (fileIdx > 69)
				continue;
			auto filePath = WilList[fileIdx];
			auto sprite = gfx->GetSprite(filePath, tile.TileIndex);
			gfx->DrawCommand(sprite, j*48, i*32, 48, 32);
		}
	}
	gfx->DrawCache();
	SDL_Delay(20000);
	delete gfx;
	SDL_DestroyWindow(window);
	SDL_Quit();
}