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
	actor->onActionStart += [this](Action *a){
		if (a->Move) {
			uint32_t ms = this->mActor->GetAction().Duration;
			this->mMapRenderer->SetScrollSpeed(a->Arg.ui / (ms / 1000.0f));
			this->mMapRenderer->Scroll(this->mActor->GetDir(), a->Arg.ui);
		}
	};
	actor->onActionCompleted += [this](Action *a) {
		this->mMapRenderer->CompleteScroll();
	};
}

void MyHeroRenderer::CaclScreenPos(int32_t & x, int32_t & y)
{
	x = (CellW * (int32_t)(floor(XCount / 2.0f)));
	y = (CellH * (int32_t)(floor(YCount / 2.0f)));
}