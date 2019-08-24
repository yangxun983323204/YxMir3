#pragma once
#include "GuiHelper.hpp"
#include "MyView.hpp"

class SelectActorView:
	public MyView
{
public:
	SelectActorView();
	~SelectActorView();
	virtual void Draw();
	virtual bool HandleEvent(SDL_Event &e);
	virtual void OnShow();
	virtual void OnHide();
public:
	YxGUI::Canvas *UI;
	YxGUI::Button *Create;
	YxGUI::Button *Delete;
	YxGUI::Button *Start;
	YxGUI::Button *Exit;
private:
	Sprite *_bg;

	void Binding();
};