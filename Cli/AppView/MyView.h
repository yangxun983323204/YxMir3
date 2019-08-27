#pragma once
#include "../SDLInc.h"
#include "../SpriteMgr.h"

class MyView
{
public:
	MyView();
	~MyView();
	virtual void Draw(uint32_t ms) {};
	virtual bool HandleEvent(SDL_Event &e) { return false; };
	virtual void OnShow() {};
	virtual void OnHide() {};
protected:
	static SpriteMgr _spriteMgr;
	static bool _inited;

public:
	// Interface1c
	const static uint16_t IdxInterface;
};