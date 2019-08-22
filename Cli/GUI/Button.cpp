#include "Button.h"

namespace YxGUI {

	Button::Button()
	{
		_image = new YxGUI::Image();
		_text = nullptr;
		AddChild(_image);
		_detector.onClick = [this](uint8_t idx) {
			if (this->onClick)
				this->onClick();
		};
	}

	Button::~Button()
	{
	}
	inline void Button::SetSprite(Sprite * sp, bool manage)
	{
		_image->SetSprite(sp, manage);
	}
	inline void Button::SetText(wstring str)
	{
		if (!_text) {
			_text = new Text();
			AddChild(_text);
		}
		_text->SetString(str);
	}
	inline void Button::Draw()
	{
		_image->Draw();
		if (_text)
			_text->Draw();
	}
	inline bool Button::HandleEvent(SDL_Event & e)
	{
		SDL_Point pos;
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			pos={ e.motion.x,e.motion.y };
			if (!HitTest(&pos))
				return false;
			_detector.Down(e.button.button, e.motion.x, e.motion.y);
			return true;
		case SDL_MOUSEBUTTONUP:
			pos={ e.motion.x,e.motion.y };
			if (!HitTest(&pos))
				return false;
			_detector.Up(e.button.button, e.motion.x, e.motion.y);
			return true;
		}
		return false;
	}
}