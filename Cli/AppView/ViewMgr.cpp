#include "ViewMgr.h"

ViewMgr::ViewMgr()
{
	_current = ViewIndex::None;
	_viewArray.push_back(new LoginView());
	_viewArray.push_back(new SelectActorView());
}

ViewMgr::~ViewMgr()
{
	auto p = _viewArray.begin();
	for (; p!=_viewArray.end(); p++)
	{
		delete (*p);
	}
	_viewArray.clear();
}

MyView * ViewMgr::Current()
{
	return _viewArray[(int)_current];
}

MyView *ViewMgr::ShowView(ViewIndex idx)
{
	if (_current!=ViewIndex::None && _current!=idx)
	{
		_viewArray[(int)_current]->OnHide();
	}
	_current = idx;
	_viewArray[(int)_current]->OnShow();
	return _viewArray[(int)_current];
}
