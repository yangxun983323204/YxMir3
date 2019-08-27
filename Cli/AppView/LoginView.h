#pragma once
#include "GuiHelper.hpp"
#include "MyView.h"

class LoginView :
	public MyView
{
public:
	LoginView();
	~LoginView();
	virtual void Draw(uint32_t ms);
	virtual bool HandleEvent(SDL_Event &e);
	virtual void OnShow();
	virtual void OnHide();
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
	void Binding();
};