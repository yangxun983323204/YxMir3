// 游戏对象渲染器
// 不管理Actor对象生命周期
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

	//void SetMapRenderer(MapRenderer *mapRenderer);
	virtual void SetActor(Actor *actor);
	virtual void Draw(uint32_t delta);
	bool HasActor();

	bool Debug;
protected:
	Sprite* GetSprite(uint32_t delta);
	void OnMotionChanged();// 当actor动作或方向变化时，更新动画帧的参数
	virtual void DrawImpl(uint32_t delta, Vector2Float pos,Sprite *actorSprite);

	Actor *mActor;
	uint8_t mImgLibIdx;
	uint8_t mEffectImgLibIdx;// todo

	AnimInstance _anim;
	Sound3D *_sound;
};