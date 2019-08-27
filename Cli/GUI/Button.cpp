#include "Button.h"

namespace YxGUI {

	Button::Button()
	{
		_press = false;
		_imageNormal = new YxGUI::Image();
		_imageNormal->HitTestTarget = false;
		AddChild(_imageNormal);

		_imageHighlight = new YxGUI::Image();
		_imageHighlight->HitTestTarget = false;
		AddChild(_imageHighlight);

		_imagePress = new YxGUI::Image();
		_imagePress->HitTestTarget = false;
		AddChild(_imagePress);

		_text = nullptr;
		
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
	void Button::SetPressSprite(Sprite * sp, bool manage)
	{
		_imagePress->SetSprite(sp, manage);
		_imagePress->SetAsNativeSize();
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
		if (_press && _imagePress->HasSprite())
		{
			_imageNormal->Visiable = false;
			_imageHighlight->Visiable = false;
			_imagePress->Visiable = true;
		}
		else if (_hover && _imageHighlight->HasSprite()) {
			_imageNormal->Visiable = false;
			_imageHighlight->Visiable = true;
			_imagePress->Visiable = false;
		}
		else {
			_imageNormal->Visiable = true;
			_imageHighlight->Visiable = false;
			_imagePress->Visiable = false;
		}
	}
	inline bool Button::HandleEvent(SDL_Event & e)
	{
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			_press = true;
			_detector.Down(e.button.button, e.motion.x, e.motion.y);
			return true;
		case SDL_MOUSEBUTTONUP:
			_press = false;
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