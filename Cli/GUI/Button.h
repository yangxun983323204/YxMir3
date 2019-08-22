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
		void SetSprite(Sprite* sp,bool manage);
		void SetText(wstring str);
		virtual void Draw();
		virtual bool HandleEvent(SDL_Event &e);
	protected:
		Image *_image;
		Text *_text;
		ClickDetector _detector;
	};
}