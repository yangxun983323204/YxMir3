#pragma once
#include <vector>
#include "../Singleton.hpp"
#include "MyView.h"
#include "LoginView.h"
#include "SelectActorView.h"

class ViewMgr:
	public Singleton<ViewMgr>
{
public:
	enum class ViewIndex {
		None = -1,
		Login = 0,
		Select,
	};
	ViewMgr();
	~ViewMgr();
	MyView *Current();
	MyView *ShowView(ViewIndex idx);
private:
	ViewIndex _current;
	std::vector<MyView*> _viewArray;
};