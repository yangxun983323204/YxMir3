#pragma once
#include "Selectable.hpp"
#include "Image.h"
#include "Text.h"
#include "ClickDetector.hpp"
#include "../Delegate.hpp"

namespace YxGUI {
	class Button
		:public Selectable
	{
	public:
		Yx::Delegate<void()> onClick;
		Button();
		~Button();
		void SetNormalSprite(Sprite* sp,bool manage);
		void SetHighLightSprite(Sprite* sp, bool manage);
		void SetText(wstring str);
		void SetAsSpriteSize();
		virtual void Draw();
		virtual bool HandleEvent(SDL_Event &e);
		virtual void OnHover(bool h);
	protected:
		Image *_imageNormal;
		Image *_imageHighlight;
		Text *_text;
		ClickDetector _detector;
		bool _hover;
	};
}