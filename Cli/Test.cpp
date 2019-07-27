#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"
#include "WILIndex.h"
#include "MapRenderer.h"

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
	delete img;
}

void TestMapLoad()
{
	Map map;
	map.Load("Map/D008.map");
	printf("map w:%d,h:%d", map.w(), map.h());
}
void TestDrawMapRect() 
{
	MyGfx *gfx = new MyGfx("map viewer",LayoutW,LayoutH);
	Map map;
	map.Load("Map/D008.map");
	int offsetX = 0;
	int offsetY = 0;
	// 绘制从左上角开始的24*24个tile
	for (size_t x = 0; x < 24; x++)
	{
		for (size_t y = 0; y < 24; y++)
		{
			auto tile = map.TileAt(x*2 + offsetY, y*2 + offsetX);// 一个tile横竖都是2个cell，因此坐标要乘以2
			int fileIdx = tile.FileIndex;
			ImageLib::ExFileIdx(fileIdx);
			if ((fileIdx % 14) > 2)
				continue;
			if (fileIdx > 69)
				continue;
			auto filePath = WilList[fileIdx];
			auto sprite = gfx->GetSprite(filePath, tile.TileIndex);
			if(sprite)
				gfx->DrawCommand(sprite, x*96, y*64,MyGfx::Layer::Bottom);
		}
	}
	gfx->DrawCache();
	SDL_Delay(5000);
	delete gfx;
}

void TestMapRender()
{
	MyGfx *gfx = new MyGfx("TestMapRender", LayoutW, LayoutH);
	Map map;
	map.Load("Map/D008.map");
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	renderer->Draw(100, 100);
	gfx->DrawCache();
	SDL_Delay(5000);
	delete renderer;
	delete gfx;
}