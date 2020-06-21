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
	window = SDL_CreateWindow("TestWIL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, img->Width, img->Height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	auto sprite = MyGfx::CreateSpriteFromImage(renderer,img);
	delete img;
	SDL_RenderCopy(renderer, sprite->GetTex(), NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	delete sprite;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
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
	auto sMgr = SpriteMgr::Main();
	gfx->mDebug = true;
	gfx->SetViewPoint(Cell2World({ 0,0 }));
	Map map;
	map.Load("Map/0.map");
	// 绘制从左上角开始的17*17个tile
	for (size_t x = 0; x < CellCountX; x++)
	{
		for (size_t y = 0; y < CellCountY; y++)
		{
			auto tile = map.TileAt(x*CellPerTileX, y*CellPerTileY);// 一个tile横竖都是2个cell，因此坐标要乘以2
			int fileIdx = tile.FileIndex;
			if(!tile.RemapFileIndex(fileIdx))
				continue;
			auto sprite = sMgr->GetSprite(fileIdx, tile.TileIndex);
			if(sprite)
				gfx->DrawCommand(sprite, x*TileW, y*TileH,MyGfx::Layer::Bottom);
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
	auto sMgr = SpriteMgr::Main();
	Map map;
	map.Load("Map/0.map");
	MapRenderer *mapRenderer = new MapRenderer();
	mapRenderer->mDebug = true;
	mapRenderer->SetMap(&map);
	mapRenderer->SetViewPoint(Cell2World({398, 397 }));
	gfx->SetViewPoint(Cell2World({ 398, 397 }));
	MoveState move;
	move.scrollSpeed = 4 / 1000.0f;
	gfx->onDraw += [gfx, mapRenderer,&move](uint32_t deltaMs) {
		if (move.IsScrolling()) {
			move.Update(deltaMs);
			auto deltaMove = Vector2Float{ move.xDelta,move.yDelta };
			mapRenderer->SetViewPointDelta(deltaMove);
			gfx->SetViewPointDelta(deltaMove);
		}
		mapRenderer->Draw(deltaMs);
		gfx->DrawCache();
	};
	gfx->onEvent += [gfx, mapRenderer,&move](SDL_Event* e) {
		if (e->type == SDL_QUIT)
			gfx->Exit();  
		else if (e->type == SDL_EventType::SDL_KEYDOWN)
		{
			if (move.IsScrolling())return;
			switch (e->key.keysym.sym)
			{
			case SDLK_UP:
				move.Set(Horizontal::None, Vertical::Up);
				break;
			case SDLK_DOWN:
				move.Set(Horizontal::None, Vertical::Down);
				break;
			case SDLK_LEFT:
				move.Set(Horizontal::Left, Vertical::None);
				break;
			case SDLK_RIGHT:
				move.Set(Horizontal::Right, Vertical::None);
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
	delete mapRenderer;
	delete sMgr;
	delete gfx;
}
void TestActorRender() 
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	gfx->mDebug = true;
	auto sMgr = SpriteMgr::Main();
	Map map;
	map.Load("Map/0.map");
	MapRenderer *mapRenderer = new MapRenderer();
	mapRenderer->mDebug = true;
	mapRenderer->SetMap(&map);
	mapRenderer->SetViewPoint(Cell2World({ 400, 390 }));
	gfx->SetViewPoint(Cell2World({ 400, 390 }));
	Hero actor;
	actor.SetMap(&map);
	actor.SetWPos(Cell2World({ 400,390 }));
	actor.SetFeature({
		ActorGender::Woman,
		8,2,32
	});
	actor.SetMotion(_MT_RUN);
	MyHeroRenderer aRenderer;
	aRenderer.SetActor(&actor);
	aRenderer.SetMapRenderer(mapRenderer);
	aRenderer.Debug = true;

	gfx->onDraw += [gfx, mapRenderer,&aRenderer,&actor](uint32_t deltaMs) {
		actor.Update(deltaMs);
		mapRenderer->Draw(deltaMs);
		aRenderer.Draw(deltaMs);
		gfx->DrawCache();
	};
	gfx->onEvent += [gfx, mapRenderer,&actor](SDL_Event* e) {
		if (e->type == SDL_QUIT)
			gfx->Exit();
		else if (e->type == SDL_EventType::SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_UP:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Up));
				break;
			case SDLK_DOWN:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Down));
				break;
			case SDLK_LEFT:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Left));
				break;
			case SDLK_RIGHT:
				actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Right));
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
	delete mapRenderer;
	delete sMgr;
	delete gfx;
}
void TestInputMgr() 
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	auto sMgr = SpriteMgr::Main();
	Map map;
	map.Load("Map/0.map");
	SoundMgr *soudMgr = SoundMgr::Instance();
	soudMgr->PlayBgm("0", true);
	Mix_VolumeMusic(20);
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	Hero actor;
	actor.SetMap(&map);
	actor.SetWPos(Cell2World({ 398,391 }));
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

	gfx->onDraw += [gfx, renderer,&input, &aRenderer, &actor,&soudMgr](uint32_t deltaMs) {
		input.Update(deltaMs);
		actor.Update(deltaMs);
		renderer->Draw(deltaMs);
		aRenderer->Draw(deltaMs);
		gfx->DrawCache();
		soudMgr->Pos = actor.GetWPos();
		soudMgr->Update();
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
void TestMidBgShadowTwinkle()
{
	MyGfx *gfx = new MyGfx(L"比奇城", LayoutW, LayoutH);
	gfx->LockFrameTime = true;
	auto sMgr = SpriteMgr::Main();
	Map map;
	map.Load("Map/0.map");
	MapRenderer *renderer = new MapRenderer();
	renderer->mDebug = true;
	renderer->SetMap(&map);
	Hero actor;
	actor.SetMap(&map);
	actor.SetWPos(Cell2World({ 388,370 }));
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
	gfx->onDraw += [gfx, renderer, &input, &aRenderer, &actor](uint32_t deltaMs) {
		actor.HandleAction(Action(_MT_WALK, ActorGender::Man, Direction::Right));
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