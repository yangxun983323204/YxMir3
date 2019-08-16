#pragma once
#include "Actor.h"
class Hero :
	public Actor
{
public:
	Hero();
	~Hero();
protected:
	void Walk(Direction dir);
	void Run(Direction dir);
	virtual void HandleActionImpl(Action act);
};

