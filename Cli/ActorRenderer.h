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

	bool Debug;
protected:
	Sprite* GetSprite(uint32_t delta);
	void CaclScreenPos(int32_t &x, int32_t &y);
	void OnMotionChanged();// ��actor��������仯ʱ�����¶���֡�Ĳ���

	MapRenderer *mMapRenderer;
	Actor *mActor;
	uint8_t mImgLibIdx;
	uint8_t mEffectImgLibIdx;// todo

	uint32_t mCurrFrame;
	uint32_t mCurrDelay;
	uint32_t mFstFrame;
	uint32_t mEndFrame;
	uint16_t mFrameDelay;
	uint16_t mFrameCount;
};