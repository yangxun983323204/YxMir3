#include "MyHeroRenderer.h"



MyHeroRenderer::MyHeroRenderer()
{
	mMapRenderer = nullptr;
}


MyHeroRenderer::~MyHeroRenderer()
{
}

void MyHeroRenderer::SetMapRenderer(MapRenderer *mapRenderer)
{
	mMapRenderer = mapRenderer;
	mMapRenderer->SetViewPoint(mActor->GetWPos());
}

void MyHeroRenderer::DrawImpl(uint32_t delta, Vector2Float pos, Sprite * actorSprite)
{
	if (mActor->GetAction().Move && !mActor->GetAction().IsDone()) {
		MyGfx::Instance()->SetViewPoint(mActor->GetWPos());
		mMapRenderer->SetViewPoint(mActor->GetWPos());
	}
	HeroRenderer::DrawImpl(delta,pos, actorSprite);
}
