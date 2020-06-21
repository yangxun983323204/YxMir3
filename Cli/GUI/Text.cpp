#include "Text.h"

namespace YxGUI {
	Text::Text()
	{
		_str = L"";
		_autoSize = false;
		_sprite = nullptr;
	}

	Text::~Text()
	{
		if (_sprite)
		{
			delete _sprite;
			_sprite = nullptr;
		}
	}
	wstring Text::GetString()
	{
		return _str;
	}
	void Text::SetString(wstring str)
	{
		if (_str != str)
		{
			_str = str;
			if (_sprite) {
				delete _sprite;
				_sprite = nullptr;
			}
			if (!_str.empty())
			{
				_sprite = MyGfx::Instance()->CreateTextSprite(_str);
				if (_autoSize)
				{
					_lRect.w = _sprite->w();
					_lRect.h = _sprite->h();
					CalcWorldRect();
				}
			}
			else {
				if (_autoSize)
				{
					_lRect.w = 0;
					_lRect.h = 0;
					CalcWorldRect();
				}
			}
		}
	}
	bool Text::GetAutoSize()
	{
		return _autoSize;
	}
	void Text::SetAutoSize(bool a)
	{
		if (_autoSize != a)
		{
			_autoSize = a;
			if (_autoSize && _sprite)
			{
				_lRect.w = _sprite->w();
				_lRect.h = _sprite->h();
				CalcWorldRect();
			}
		}
	}
	void Text::Draw()
	{
		if (_sprite)
			MyGfx::Instance()->DrawCommand(_sprite, _wRect.x, _wRect.y, _wRect.w, _wRect.h, MyGfx::Layer::GUI);
	}
}