#pragma once
#include "HeroRenderer.h"

class MyHeroRenderer :
	public HeroRenderer
{
public:
	MyHeroRenderer();
	~MyHeroRenderer();

	void SetMapRenderer(MapRenderer *mapRenderer);
protected:
	MapRenderer *mMapRenderer;

	virtual void DrawImpl(uint32_t delta, Vector2Float pos, Sprite *actorSprite);
};