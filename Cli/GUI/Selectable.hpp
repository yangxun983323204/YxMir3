#pragma once
#include "Graphic.h"

namespace YxGUI {
	class Selectable :public Graphic 
	{
	public:
		Selectable() {
			HitTestTarget = true;
			_interactive = true;
		}
		~Selectable() {}
		virtual bool HandleEvent(SDL_Event &e) {
			return false;
		}
		virtual void OnHover(bool h) {};
		virtual void OnFocus(bool f) {};
	protected:

	};
}