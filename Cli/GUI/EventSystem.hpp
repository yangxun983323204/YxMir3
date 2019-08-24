#pragma once
#include <list>
#include <stack>
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
			// 深度优先遍历节点
			_frameSelectObjs.clear();
			if (_root->Visiable && _root->_children.size()>0)
			{
				auto p = _root->_children.rbegin();
				for (; p != _root->_children.rend(); p++)
				{
					if ((*p)->Visiable)
						_frameGraphicObjs.push((*p));
				}
			}
			while (!_frameGraphicObjs.empty())
			{
				Graphic *g = _frameGraphicObjs.top();
				_frameGraphicObjs.pop();
				if(g->HitTestTarget)
					_frameSelectObjs.push_front(g);
				if (g->_children.size() > 0) {
					auto p = g->_children.rbegin();
					for (; p != g->_children.rend(); p++)
					{
						if ((*p)->Visiable)
							_frameGraphicObjs.push((*p));
					}
				}
			}
			bool isMouseEvent = false;
			if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
				isMouseEvent = true;
			if (isMouseEvent)
			{
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
			}
			else {
				if (_focus)
					return _focus->HandleEvent(e);
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
		std::stack<Graphic*> _frameGraphicObjs;
		Graphic *_root;
		Selectable *_focus;
		Selectable *_hover;
	};
}
