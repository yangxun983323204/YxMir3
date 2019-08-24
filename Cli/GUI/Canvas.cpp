#include "Canvas.h"
#include "Graphic.h"

using namespace YxGUI;

Canvas::Canvas()
{
	_eventSystem = new EventSystem(this);
	_frameSelectObjs.resize(20);
}

Canvas::~Canvas()
{
	delete _eventSystem;
}
void Canvas::Draw()
{
	// 深度优先遍历节点
	if (Visiable)
	{
		if (Visiable && _children.size()>0)
		{
			auto p = _children.rbegin();
			for (; p != _children.rend(); p++)
			{
				if ((*p)->Visiable)
					_frameGraphicObjs.push((*p));
			}
		}
	}
	while (!_frameGraphicObjs.empty())
	{
		Graphic *g = _frameGraphicObjs.top();
		_frameGraphicObjs.pop();
		if(g->Visiable)
			g->Draw();
		auto p = g->_children.rbegin();
		for (; p != g->_children.rend(); p++)
		{
			if ((*p)->Visiable)
				_frameGraphicObjs.push((*p));
		}
	}

}
bool Canvas::HandleEvent(SDL_Event & e)
{
	return _eventSystem->HandleEvent(e);
	_frameSelectObjs.clear();
}

void YxGUI::Canvas::Reset()
{
	_eventSystem->ClearFocus();
}
