#include "Button.h"

namespace YxGUI {

	Button::Button()
	{
		_hover = false;
		_imageNormal = new YxGUI::Image();
		_imageNormal->HitTestTarget = false;
		_imageHighlight = new YxGUI::Image();
		_imageHighlight->HitTestTarget = false;
		_text = nullptr;
		AddChild(_imageNormal);
		AddChild(_imageHighlight);
		_detector.onClick = [this](uint8_t idx) {
			if (this->onClick)
				this->onClick();
		};
	}

	Button::~Button()
	{
	}
	void Button::SetNormalSprite(Sprite * sp, bool manage)
	{
		_imageNormal->SetSprite(sp, manage);
		_imageNormal->SetAsNativeSize();
	}
	void Button::SetHighLightSprite(Sprite * sp, bool manage)
	{
		_imageHighlight->SetSprite(sp, manage);
		_imageHighlight->SetAsNativeSize();
	}
	inline void Button::SetText(wstring str)
	{
		if (!_text) {
			_text = new Text();
			AddChild(_text);
			_text->HitTestTarget = false;
		}
		_text->SetString(str);
	}
	void Button::SetAsSpriteSize()
	{
		auto rect = _imageNormal->GetLocalRect();
		SetLocalSize(rect.w, rect.h);
	}
	inline void Button::Draw()
	{
		if (_hover && _imageHighlight->HasSprite()) {
			_imageNormal->Visiable = false;
			_imageHighlight->Visiable = true;
		}
		else {
			_imageNormal->Visiable = true;
			_imageHighlight->Visiable = false;
		}
	}
	inline bool Button::HandleEvent(SDL_Event & e)
	{
		SDL_Point pos;
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			_hover = false;
			_detector.Down(e.button.button, e.motion.x, e.motion.y);
			return true;
		case SDL_MOUSEBUTTONUP:
			_hover = true;
			_detector.Up(e.button.button, e.motion.x, e.motion.y);
			return true;
		}
		return false;
	}
	void Button::OnHover(bool h)
	{
		_hover = h;
	}
}