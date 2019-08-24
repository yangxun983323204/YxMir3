#pragma once
#include "Graphic.h"

namespace YxGUI {
	class Selectable :public Graphic 
	{
	public:
		Selectable() {
			_focus = false;
			_hover = false;
			HitTestTarget = true;
			_interactive = true;
		}
		~Selectable() {}
		virtual void Draw() {};
		virtual bool HandleEvent(SDL_Event &e) {
			return false;
		}
		virtual void OnHover(bool h) {};
		virtual void OnFocus(bool f) {};
	protected:
		bool _focus;
		bool _hover;
	};
}