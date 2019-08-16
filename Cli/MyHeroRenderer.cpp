#include "MyHeroRenderer.h"



MyHeroRenderer::MyHeroRenderer()
{
}


MyHeroRenderer::~MyHeroRenderer()
{
}

void MyHeroRenderer::SetActor(Actor * actor)
{
	ActorRenderer::SetActor(actor);
	actor->onMove = [this](Direction dir,uint16_t count){
		uint32_t ms = this->mActor->GetAction().Duration;
		this->mMapRenderer->SetScrollSpeed(count/(ms/1000.0f));
		this->mMapRenderer->Scroll(dir, count);
	};
}

void MyHeroRenderer::CaclScreenPos(int32_t & x, int32_t & y)
{
	x = (CellW * XCount / 2);
	y = (CellH * YCount / 2);
}