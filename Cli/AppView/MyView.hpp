#pragma once
#include "../SDLInc.h"

class MyView
{
public:
	MyView() {};
	~MyView() {};
	virtual void Draw() {};
	virtual bool HandleEvent(SDL_Event &e) { return false; };
	virtual void OnShow() {};
	virtual void OnHide() {};
private:

};