#include "SDLInc.h"
#include <stdio.h>
#include "Test.h"
#include "Common.h"
#include "Singleton.hpp"
#include "Delegate.hpp"
#include "MyGfx.h"
#include "SpriteMgr.h"
#include "SoundMgr.h"
#include "InputMgr.h"
#include "./AppView/ViewMgr.h"


int main(int argc, char* argv[])
{
	Test();
	MyGfx *gfx = new MyGfx(L"YxMir3", 800, 600);
	auto sMgr = SpriteMgr::Main();
	SoundMgr *soudMgr = SoundMgr::Instance();
	InputMgr input;
	auto viewMgr = ViewMgr::Instance();
	viewMgr->ShowView(ViewMgr::ViewIndex::Login);
	input.SetGfx(gfx);
	input.onSysQuit += [&gfx]() { gfx->Exit(); };
	input.onUICheck = [viewMgr](SDL_Event *e) {
		return viewMgr->Current()->HandleEvent(*e);
	};

	gfx->onDraw += [gfx, &input, &soudMgr,&viewMgr](uint32_t deltaMs) {
		input.Update(deltaMs);
		soudMgr->Update();
		viewMgr->Current()->Draw(deltaMs);
		gfx->DrawCache();
	};

	gfx->RunLoop();
	delete viewMgr;
	SoundMgr::Destroy();
	delete sMgr;
	delete gfx;
	return 0;
}