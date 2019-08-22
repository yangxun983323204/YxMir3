#include "Canvas.h"
using namespace YxGUI;

Canvas::Canvas()
{
	_frameSelectObjs.resize(20);
}

Canvas::~Canvas()
{
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
		Graphic *g = _frameGraphicObjs.top();
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
	_frameSelectObjs.clear();
	if (Visiable)
	{
		for each (auto g in _children)
		{
			if (g->Visiable && g->HitTestTarget && typeid(g) == typeid(Selectable*))
				_frameGraphicObjs.push(g);
		}
	}
	while (!_frameGraphicObjs.empty())
	{
		Graphic *g = _frameGraphicObjs.top();
		_frameGraphicObjs.pop();
		g->Draw();
		_frameSelectObjs.push_front((Selectable*)g);
		for each (auto g in g->_children)
		{
			if (g->Visiable && g->HitTestTarget && typeid(g) == typeid(Selectable*))
				_frameGraphicObjs.push(g);
		}
	}
	for each (auto g in _frameSelectObjs)
	{
		if (g->HandleEvent(e))
			return true;
	}
	return false;
}