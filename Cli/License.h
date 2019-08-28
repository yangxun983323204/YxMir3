#pragma once
#include "MyGfx.h"
class License
{
public:
	static void DrawLicense();
private:
	static bool _inited;
	static Sprite *_sprite;
	static void Init();
};

