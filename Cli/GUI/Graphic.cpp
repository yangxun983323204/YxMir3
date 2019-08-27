#include "Graphic.h"

using namespace YxGUI;

Graphic::Graphic()
{
	Visiable = true;
	HitTestTarget = true;
	_interactive = false;
	_parent = nullptr;
	_lRect = {0,0,100,50};
	_focus = false;
	_idxInParent = 0;
	_lScaleX = _lScaleY = 1;
	CalcWorldRect();
}


Graphic::~Graphic()
{
	for (auto iter = _children.begin(); iter != _children.end();)
	{
		delete *iter;
		iter = _children.erase(iter);
	}
}

void YxGUI::Graphic::SetLocalPos(int x, int y)
{
	_lRect.x = x;
	_lRect.y = y;
	CalcWorldRect();
}

void YxGUI::Graphic::SetLocalSize(uint32_t w, uint32_t h)
{
	_lRect.w = w;
	_lRect.h = h;
	CalcWorldRect();
}

SDL_Rect YxGUI::Graphic::GetLocalRect()
{
	return _lRect;
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
	g->CalcWorldRect();
}

void YxGUI::Graphic::RemoveChild(Graphic * g)
{
	if (g->_parent == this) {
		_children.remove(g);
		g->_parent = nullptr;
		g->_idxInParent = 0;
		g->CalcWorldRect();
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
	g->CalcWorldRect();
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
	return SDL_PointInRect(p, &_wRect) == SDL_bool::SDL_TRUE;
}

float YxGUI::Graphic::GetLocalScaleX()
{
	return _lScaleX;
}

void YxGUI::Graphic::SetLocalScaleX(float sx)
{
	_lScaleX = sx;
	CalcWorldRect();
}

float YxGUI::Graphic::GetLocalScaleY()
{
	return _lScaleY;
}

void YxGUI::Graphic::SetLocalScaleY(float sy)
{
	_lScaleY = sy;
	CalcWorldRect();
}

void YxGUI::Graphic::CalcWorldRect()
{
	if (_parent)
	{
		_wScaleX = _parent->_wScaleX * _lScaleX;
		_wScaleY = _parent->_wScaleY * _lScaleY;
	}
	else
	{
		_wScaleX = _lScaleX;
		_wScaleY = _lScaleY;
	}
	_wRect = _lRect;
	if (_parent)
	{
		_wRect.x += _parent->_wRect.x;
		_wRect.y += _parent->_wRect.y;
		_wRect.w *= _wScaleX;
		_wRect.h *= _wScaleY;
	}
	else 
	{
		_wRect.w = (int)(_wRect.w * _lScaleX);
		_wRect.h = (int)(_wRect.h * _lScaleY);
	}
	// 更新子元素
	for (auto iter = _children.begin(); iter != _children.end();iter++)
	{
		(*iter)->CalcWorldRect();
	}
}
