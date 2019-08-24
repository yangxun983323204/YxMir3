#include "InputMgr.h"
#include <cmath>

InputMgr::InputMgr()
{
	_gfx = nullptr;
}


InputMgr::~InputMgr()
{
}

void InputMgr::Update(uint32_t ms)
{
	HandleMouse();
}

void InputMgr::SetGfx(MyGfx * gfx)
{
	if (_gfx)
	{
		_gfx->onEvent -= Yx::BindClassFunc(&InputMgr::OnSdlEvent, this);
	}
	if (gfx)
	{
		_gfx = gfx;
		_gfx->onEvent += Yx::BindClassFunc(&InputMgr::OnSdlEvent, this);
	}
}

void InputMgr::HandleMouse()
{
	Vector2Int pos{ _mousePos.x - LayoutW / 2, _mousePos.y - LayoutH / 2 };
	int rawAngle = (int(atan2(pos.y, pos.x) * Rad2Deg) + 360)%360;
	int clockwizeAngle = (rawAngle + 90 + 22) % 360;
	Direction dir = (Direction)((int)floor(clockwizeAngle / 45.0f));
	if (_mouseStatus[SDL_BUTTON_LEFT]==1)
	{
		// todo hasTarget
		if (onWalk)
			onWalk(dir);
	}
	else if (_mouseStatus[SDL_BUTTON_RIGHT] == 1)
	{
		if (onRun)
			onRun(dir);
	}
}

void InputMgr::OnSdlEvent(SDL_Event *e)
{
	if (e->type == SDL_QUIT)
	{
		if (onSysQuit)
			onSysQuit();
	}
	else
	{
		if (!onUICheck || !onUICheck(e))// UI未处理事件
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				_mouseStatus[e->button.button] = 1;
				_mousePos.x = e->motion.x;
				_mousePos.y = e->motion.y;
			}
			else if (e->type == SDL_MOUSEMOTION)
			{
				_mousePos.x = e->motion.x;
				_mousePos.y = e->motion.y;
			}
			else if (e->type == SDL_MOUSEBUTTONUP)
			{
				_mouseStatus[e->button.button] = 0;
			}
		}
	}
	
}
