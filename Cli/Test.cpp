#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"
#include "WILIndex.h"
#include "MapRenderer.h"
#include "SpriteMgr.h"
#include "Actor.h"
#include "ActorRenderer.h"
#include "HeroRenderer.h"
#include "Hero.h"
#include "MyHeroRenderer.h"
#include "InputMgr.h"
#include "SoundMgr.h"

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
	SDL_Delay(1000);
	SDL_FreeSurface(sprite->Surface);
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
	delete img;
}
void TestMapLoad()
{
	Map map;
	map.Load("Map/0.map");
	printf("map w:%d,h:%d", map.w(), map.h());
}
void TestDrawMapRect() 
{
	MyGfx *gfx = new MyGfx(L"map viewer",LayoutW,LayoutH);
	auto sMgr = SpriteMgr::Instance();
	gfx->mDebug = true;
	Map map;
	map.Load("Map/0.map");
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
			auto sprite = sMgr->GetSprite(fileIdx, tile.TileIndex);
			if(sprite)
				gfx->DrawCommand(sprite, x*96, y*64,MyGfx::Layer::Bottom);
		}
	}
	gfx->DrawCache();
	gfx->onEvent += [gfx](SDL_Event* e) { 
		if(e->type == SDL_QUIT)
			gfx->Exit(); 
	};
	gfx->RunLoop();
	delete sMgr;
	delete gfx;
}
void TestMapRender()
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	auto sMgr = SpriteMgr::Instance();
	Map map;
	map.Load("Map/0.map");
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	renderer->SetPos(Vector2UInt{ 400, 400 });
	gfx->onDraw += [gfx, renderer](uint32_t deltaMs) {
		renderer->Draw(deltaMs);
		gfx->DrawCache();
	};
	gfx->onEvent += [gfx, renderer](SDL_Event* e) {
		if (e->type == SDL_QUIT)
			gfx->Exit();  
		else if (e->type == SDL_EventType::SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_UP:
				renderer->Scroll(Horizontal::None, Vertical::Up);
				break;
			case SDLK_DOWN:
				renderer->Scroll(Horizontal::None, Vertical::Down);
				break;
			case SDLK_LEFT:
				renderer->Scroll(Horizontal::Left, Vertical::None);
				break;
			case SDLK_RIGHT:
				renderer->Scroll(Horizontal::Right, Vertical::None);
				break;
			default:
				break;
			}
		}
		else if (e->type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.button == 1) {

			}
		}
	};
	gfx->RunLoop();
	delete renderer;
	delete sMgr;
	delete gfx;
}
void TestActorRender() 
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	auto sMgr = SpriteMgr::Instance();
	Map map;
	map.Load("Map/0.map");
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	renderer->SetPos(Vector2UInt{ 400, 390 });

	Hero actor;
	actor.SetPos({ 400,390 });
	actor.SetFeature({
		ActorGender::Woman,
		8,2,32
	});
	actor.SetMotion(_MT_RUN);
	MyHeroRenderer aRenderer;
	aRenderer.SetActor(&actor);
	aRenderer.SetMapRenderer(renderer);
	aRenderer.Debug = true;

	gfx->onDraw += [gfx, renderer,&aRenderer,&actor](uint32_t deltaMs) {
		actor.Update(deltaMs);
		renderer->Draw(deltaMs);
		aRenderer.Draw(deltaMs);
		gfx->DrawCache();
	};
	gfx->onEvent += [gfx, renderer,&actor](SDL_Event* e) {
		if (e->type == SDL_QUIT)
			gfx->Exit();
		else if (e->type == SDL_EventType::SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_UP:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Up));
				//actor.SetDir(Direction::Up);
				//renderer->Scroll(Map::Horizontal::None, Map::Vertical::Up);
				break;
			case SDLK_DOWN:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Down));
				//actor.SetDir(Direction::Down);
				//renderer->Scroll(Map::Horizontal::None, Map::Vertical::Down);
				break;
			case SDLK_LEFT:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Left));
				//actor.SetDir(Direction::Left);
				//renderer->Scroll(Map::Horizontal::Left, Map::Vertical::None);
				break;
			case SDLK_RIGHT:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Right));
				//actor.SetDir(Direction::Right);
				//renderer->Scroll(Map::Horizontal::Right, Map::Vertical::None);
				break;
			default:
				break;
			}
		}
		else if (e->type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
		{
			if (e->button.button == 1) {

			}
		}
	};
	gfx->RunLoop();
	delete renderer;
	delete sMgr;
	delete gfx;
}
void TestInputMgr() 
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	auto sMgr = SpriteMgr::Instance();
	Map map;
	map.Load("Map/0.map");
	SoundMgr *soudMgr = SoundMgr::Instance();
	soudMgr->PlayBgm("0", true);
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	Hero actor;
	actor.SetMap(&map);
	actor.SetPos({ 398,391 });
	actor.SetFeature({
		ActorGender::Woman,
		8,2,32
	});
	actor.HandleAction(Action(_MT_STAND, ActorGender::Man, Direction::Down));
	MyHeroRenderer *aRenderer = new MyHeroRenderer();
	aRenderer->SetActor(&actor);
	aRenderer->SetMapRenderer(renderer);
	aRenderer->Debug = true;

	InputMgr input;
	input.SetGfx(gfx);
	input.onSysQuit += [&gfx]() { gfx->Exit(); };
	input.onWalk += [&actor](Direction dir) { actor.HandleAction(Action(_MT_WALK,ActorGender::Man,dir)); };
	input.onRun += [&actor](Direction dir) { actor.HandleAction(Action(_MT_RUN, ActorGender::Man, dir)); };

	gfx->onDraw += [gfx, renderer,&input, &aRenderer, &actor](uint32_t deltaMs) {
		input.Update(deltaMs);
		actor.Update(deltaMs);
		renderer->Draw(deltaMs);
		aRenderer->Draw(deltaMs);
		gfx->DrawCache();
	};

	gfx->RunLoop();
	delete aRenderer;
	delete renderer;
	SoundMgr::Destroy();
	delete sMgr;
	delete gfx;
}
void TestSoundMgr_LoadList()
{
	SoundMgr *soudMgr = SoundMgr::Instance();
	SoundMgr::Destroy();
}