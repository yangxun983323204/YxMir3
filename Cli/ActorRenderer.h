// ��Ϸ������Ⱦ��
// ������Actor������������
#pragma once
#include "Actor.h"
#include "ImageLib.h"
#include "MapRenderer.h"

class ActorRenderer
{
public:
	ActorRenderer();
	~ActorRenderer();

	void SetMapRenderer(MapRenderer *mapRenderer);
	void SetActor(Actor *actor);
	void Draw(uint32_t delta);
	bool HasActor();
private:
	bool IsFarLeftScreen();

	MapRenderer *mMapRenderer;
	Actor *mActor;
	uint8_t mImgLibIdx;
	uint8_t mEffectImgLibIdx;// todo
	uint32_t mCurrFrame;
	uint32_t mCurrDelay;
};