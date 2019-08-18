#pragma once
#include "Actor.h"
class Hero :
	public Actor
{
public:
	Hero();
	~Hero();
protected:
	bool Hero::Walk(Action &act);
	bool Hero::Run(Action &act);
	virtual bool HandleActionImpl(Action &act);
};