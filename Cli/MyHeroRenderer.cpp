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
	actor->onMove = [this](Direction dir,uint16_t speed){
		this->mMapRenderer->SetScrollSpeed(speed);
		this->mMapRenderer->Scroll(dir);
	};
}

void MyHeroRenderer::CaclScreenPos(int32_t & x, int32_t & y)
{
	x = (CellW * XCount / 2);
	y = (CellH * YCount / 2);
}
