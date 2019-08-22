#pragma once
#include "../SDLInc.h"
#include "../GUI/Graphic.h"
#include "../GUI/Canvas.h"
#include "../GUI/Image.h"
#include "../GUI/Button.h"

class LoginView 
{
public:
	LoginView();
	~LoginView();
	void Draw();
	bool HandleEvent(SDL_Event &e);
public:
	YxGUI::Canvas *UI;
	YxGUI::Image *Bg;
	YxGUI::Button *Login;
	YxGUI::Button *Exit;
private:
	ImageLib _lib;
};