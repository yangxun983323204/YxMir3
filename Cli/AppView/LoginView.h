#pragma once
#include "GuiHelper.hpp"

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
	YxGUI::Image *Border;
	YxGUI::Button *Login;
	YxGUI::Button *New;
	YxGUI::Button *Change;
	YxGUI::Button *Exit;
	YxGUI::Image *InputBg;
	YxGUI::InputField *ID;
	YxGUI::InputField *PW;
private:
};