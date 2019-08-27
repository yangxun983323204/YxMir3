#pragma once
#include "GuiHelper.hpp"
#include "MyView.h"

class SelectActorView:
	public MyView
{
public:
	struct Role
	{
		std::wstring Name;
		uint8_t Gender;
		uint8_t Job;
	};
	SelectActorView();
	~SelectActorView();
	virtual void Draw(uint32_t ms);
	virtual bool HandleEvent(SDL_Event &e);
	virtual void OnShow();
	virtual void OnHide();
	void SetRoleList(Role roles[],uint8_t size);
public:
	YxGUI::Canvas *UI;
	YxGUI::Button *Create;
	YxGUI::Button *Delete;
	YxGUI::Button *Start;
	YxGUI::Button *Exit;
private:
	Sprite *_bg;// mgrπ‹¿Ì
	Role _roles[3];
	uint8_t _idxSelect;
	uint8_t _roleCount;

	void Binding();
};