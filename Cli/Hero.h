#pragma once
#include "Actor.h"
class Hero :
	public Actor
{
public:
	Hero();
	~Hero();

	void Walk(Direction dir);
	void Run(Direction dir);
protected:
	
};

