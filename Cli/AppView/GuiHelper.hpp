#pragma once
#include "../SDLInc.h"
#include "../GUI/Graphic.h"
#include "../GUI/Canvas.h"
#include "../GUI/Image.h"
#include "../GUI/Button.h"

class GuiHelper
{
public:
	GuiHelper(ImageLib *lib)
	{
		_lib = lib;
	}
	YxGUI::Image *CreateImage(uint32_t idx,bool manageSp = true)
	{
		auto img = new YxGUI::Image();
		auto raw = _lib->LoadImage(idx);
		img->SetSprite(MyGfx::CreateSpriteFromImage(raw), manageSp);
		img->SetAsNativeSize();
		return img;
	}
	YxGUI::Button *CreateButton(uint32_t idx, bool manageSp = true)
	{
		auto btn = new YxGUI::Button();
		auto raw0 = _lib->LoadImage(idx);
		auto raw1 = _lib->LoadImage(idx+1);
		btn->SetNormalSprite(MyGfx::CreateSpriteFromImage(raw0), manageSp);
		btn->SetHighLightSprite(MyGfx::CreateSpriteFromImage(raw1), manageSp);
		btn->SetAsSpriteSize();
		return btn;
	}

private:
	ImageLib *_lib;
};
