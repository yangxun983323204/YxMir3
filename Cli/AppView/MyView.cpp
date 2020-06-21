#include "MyView.h"

SpriteMgr* MyView::_spriteMgr = nullptr;
bool MyView::_inited = false;
const uint16_t MyView::IdxInterface = 0;

MyView::MyView()
{
	if (!_inited)
	{
		_spriteMgr = new SpriteMgr();
		_inited = true;
		_spriteMgr->ManulInitLibs(0, ".\\Data\\Interface1c.wil");
	}
}

MyView::~MyView()
{
	if (_spriteMgr)
	{
		delete _spriteMgr;
		_spriteMgr = nullptr;
	}
}