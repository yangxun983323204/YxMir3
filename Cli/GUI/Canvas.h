#pragma once
#include "Graphic.h"
#include "Selectable.hpp"
#include <list>
#include <queue>
#include "EventSystem.hpp"

namespace YxGUI {
	class Canvas:
		public Graphic
	{
	public:
		Canvas();
		~Canvas();
		void Draw();
		bool HandleEvent(SDL_Event &e);
		void Reset();// 有UI移除时必须调用，否则可能产生野指针
	private:
		std::list<Graphic*> _frameSelectObjs;
		std::queue<Graphic*> _frameGraphicObjs;
		EventSystem *_eventSystem;
	};
}