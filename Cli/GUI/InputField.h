#pragma once
#include "Selectable.hpp"
#include "Image.h"
#include "Text.h"
#include <string>

namespace YxGUI {
	using std::wstring;

	class InputField
		:public Selectable
	{
	public:
		bool IsPassword;
		InputField();
		~InputField();
		void SetBackground(Sprite *sp, bool manageSp);
		void SetAsBgSize();
		wstring GetText();
		void SetText(wstring str);
		virtual void Draw();
		virtual bool HandleEvent(SDL_Event &e);
		virtual void OnFocus(bool f);
	protected:
		YxGUI::Image *_bg;
		YxGUI::Image *_cursor;
		YxGUI::Text *_text;
		bool _focus;
		wstring _str;
	};
}