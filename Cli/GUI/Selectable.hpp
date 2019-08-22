#pragma once
#include "Graphic.h"

namespace YxGUI {
	class Selectable :public Graphic 
	{
	public:
		Selectable();
		~Selectable();
		virtual bool HandleEvent(SDL_Event &e);
	protected:

	};

	inline YxGUI::Selectable::Selectable()
	{
	}

	inline YxGUI::Selectable::~Selectable()
	{
	}
	inline bool YxGUI::Selectable::HandleEvent(SDL_Event &e)
	{
		return false;
	}
}