#include "MyView.h"


bool MyView::_inited = false;
SpriteMgr MyView::_spriteMgr;
const uint16_t MyView::IdxInterface = 0;

MyView::MyView()
{
	if (!_inited)
	{
		_inited = true;
		_spriteMgr.ManulInitLibs(0, ".\\Data\\Interface1c.wil");
	}
}

MyView::~MyView()
{}