#include "Graphic.h"

using namespace YxGUI;

Graphic::Graphic()
{
	_parent = nullptr;
	_rect={0,0,100,50};
	_focus = false;
	_idxInParent = 0;
	_scaleX = _scaleY = 1;
}


Graphic::~Graphic()
{
	for (auto iter = _children.begin(); iter != _children.end();)
	{
		delete *iter;
		iter = _children.erase(iter);
	}
}

void YxGUI::Graphic::SetRect(SDL_Rect & rect)
{
	_rect = rect;
}

SDL_Rect YxGUI::Graphic::GetRect()
{
	return _rect;
}

void YxGUI::Graphic::AddChild(Graphic * g)
{
	if (g->_parent == this)
		return;

	if (g->_parent!=nullptr)
	{
		g->_parent->RemoveChild(g);
	}
	_children.push_back(g);
	g->_parent = this;
	g->_idxInParent = _children.size()-1;
}

void YxGUI::Graphic::RemoveChild(Graphic * g)
{
	if (g->_parent == this) {
		_children.remove(g);
		g->_parent = nullptr;
		g->_idxInParent = 0;
	}
}

void YxGUI::Graphic::InsertChild(Graphic * g, uint32_t idx)
{
	if (g->_parent == this)
		return;
	if (idx >= _children.size())
	{
		AddChild(g);
		return;
	}
	g->_parent->RemoveChild(g);
	auto it = _children.begin();
	for (int i = 0; i < idx; i++)
	{
		it ++;
	}

	_children.insert(it,g);
	g->_parent = this;
	g->_idxInParent = idx;
}

uint32_t YxGUI::Graphic::GetIndexInParent()
{
	return _idxInParent;
}

void YxGUI::Graphic::SetIndexInParent(uint32_t idx)
{
	if (_parent)
	{
		_parent->RemoveChild(this);
		_parent->InsertChild(this, idx);
	}
}

bool YxGUI::Graphic::HitTest(SDL_Point *p)
{
	return SDL_PointInRect(p, &_rect);
}
