// ��Ϸ������Ⱦ��
// ������Actor������������
#pragma once
#include "Actor.h"
#include "ImageLib.h"
#include "MapRenderer.h"
#include "Sound3D.h"

class ActorRenderer
{
public:
	ActorRenderer();
	~ActorRenderer();

	void SetMapRenderer(MapRenderer *mapRenderer);
	virtual void SetActor(Actor *actor);
	virtual void Draw(uint32_t delta);
	bool HasActor();

	bool Debug;
protected:
	Sprite* GetSprite(uint32_t delta);
	virtual void CaclScreenPos(int32_t &x, int32_t &y);
	void OnMotionChanged();// ��actor��������仯ʱ�����¶���֡�Ĳ���
	virtual void DrawImpl(uint32_t delta,Vector2Int pos,Sprite *actorSprite);

	MapRenderer *mMapRenderer;
	Actor *mActor;
	uint8_t mImgLibIdx;
	uint8_t mEffectImgLibIdx;// todo

	AnimInstance _anim;
	Sound3D *_sound;
};