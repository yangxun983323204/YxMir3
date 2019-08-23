#pragma once
#include <list>
#include <queue>
#include "Graphic.h"
#include "Selectable.hpp"

namespace YxGUI {
	class EventSystem
	{
	public:
		EventSystem(Graphic *root) {
			_root = root;
			_focus = nullptr;
			_hover = nullptr;
		}
		~EventSystem() {
			_focus = nullptr; 
			_hover = nullptr;
		}
		bool HandleEvent(SDL_Event &e)
		{
			_frameSelectObjs.clear();
			if (_root->Visiable)
			{
				for each (auto g in _root->_children)
				{
					if (g->Visiable && g->HitTestTarget)
						_frameGraphicObjs.push(g);
				}
			}
			while (!_frameGraphicObjs.empty())
			{
				Graphic *g = _frameGraphicObjs.front();
				_frameGraphicObjs.pop();
				_frameSelectObjs.push_front(g);
				for each (auto g in g->_children)
				{
					if (g->Visiable && g->HitTestTarget)
						_frameGraphicObjs.push(g);
				}
			}
			SDL_Point pos{ e.motion.x,e.motion.y };
			for each (auto g in _frameSelectObjs)
			{
				if (g->HitTest(&pos))
				{
					if (_hover && (void*)_hover != (void*)g)
						_hover->OnHover(false);
					if (g->_interactive)
					{
						Selectable* p = (Selectable*)g;
						_hover = p;
						_hover->OnHover(true);
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							if (_focus && (void*)_focus != (void*)g)
								_focus->OnFocus(false);
							_focus = p;
							_focus->OnFocus(true);
						}
						p->HandleEvent(e);
					}
					return true;
				}
			}
			if (_hover)
			{
				_hover->OnHover(false);
				_hover = nullptr;
			}
			return false;
		}

		void ClearFocus() 
		{
			if (_focus) {
				_focus->OnFocus(false);
			}
			_focus = nullptr;
			if (_hover) {
				_hover->OnHover(false);
			}
			_hover = nullptr;
		}

	private:
		std::list<Graphic*> _frameSelectObjs;
		std::queue<Graphic*> _frameGraphicObjs;
		Graphic *_root;
		Selectable *_focus;
		Selectable *_hover;
	};
}
