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
	if (Visiable)
	{
		for each (auto g in _children)
		{
			if (g->Visiable)
				_frameGraphicObjs.push(g);
		}
	}
	while (!_frameGraphicObjs.empty())
	{
		Graphic *g = _frameGraphicObjs.front();
		_frameGraphicObjs.pop();
		g->Draw();
		for each (auto g in g->_children)
		{
			if (g->Visiable)
				_frameGraphicObjs.push(g);
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
