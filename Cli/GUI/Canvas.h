#pragma once
#include "Graphic.h"
#include "Selectable.hpp"
#include <list>
#include <stack>

namespace YxGUI {
	class Canvas:
		public Graphic
	{
	public:
		Canvas();
		~Canvas();
		void Draw();
		bool HandleEvent(SDL_Event &e);
	private:
		std::list<Selectable*> _frameSelectObjs;
		std::stack<Graphic*> _frameGraphicObjs;
	};
}