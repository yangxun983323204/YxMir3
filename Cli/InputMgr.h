#pragma once
#include "Delegate.hpp"
#include "Common.h"
#include "SDLInc.h"
#include "MyGfx.h"
#include <map>

class InputMgr
{
public:
	Yx::Delegate<void(Direction dir)> onWalk;
	Yx::Delegate<void(Direction dir)> onRun;
	Yx::Delegate<void(Vector2UInt pos)> onTarget;
	Yx::Delegate<void(Direction dir)> onGather;

	Yx::Delegate<void()> onSysQuit;

	InputMgr();
	~InputMgr();
	void Update(uint32_t ms);
	void SetGfx(MyGfx* gfx);
private:
	MyGfx* _gfx;
	std::map<int32_t, uint8_t> _keyStatus;
	std::map<int32_t, uint8_t> _mouseStatus;
	Vector2Int _mousePos;

	void HandleMouse();
	void OnSdlEvent(SDL_Event* e);
};

