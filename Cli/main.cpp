#include "SDLInc.h"
#include <stdio.h>
//#include "Test.h"
#include "Common.h"
#include "Singleton.hpp"
#include "Delegate.hpp"
#include "MyGfx.h"
#include "SpriteMgr.h"
#include "SoundMgr.h"
#include "InputMgr.h"
#include "./AppView/LoginView.h"


int main(int argc, char* argv[])
{
	//Test();
	MyGfx *gfx = new MyGfx(L"YxMir3", 800, 600);
	auto sMgr = SpriteMgr::Instance();
	SoundMgr *soudMgr = SoundMgr::Instance();
	soudMgr->PlayMusic("start.mp3", true);
	InputMgr input;
	LoginView *login = new LoginView();
	input.SetGfx(gfx);
	input.onSysQuit += [&gfx]() { gfx->Exit(); };
	input.onUICheck = [login](SDL_Event *e) {
		return login->HandleEvent(*e);
	};

	gfx->onDraw += [gfx, &input, &soudMgr,&login](uint32_t deltaMs) {
		input.Update(deltaMs);
		soudMgr->Update();
		login->Draw();
		gfx->DrawCache();
	};

	gfx->RunLoop();
	delete login;
	SoundMgr::Destroy();
	delete sMgr;
	delete gfx;
	return 0;
}