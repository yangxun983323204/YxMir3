#include "Image.h"

namespace YxGUI {

	Image::Image()
	{
		_sprite = nullptr;
	}

	Image::~Image()
	{
	}
	void Image::SetSprite(Sprite * sprite, bool manage)
	{
		if (_sprite && _manageImg)
		{
			delete _sprite;
			_sprite = nullptr;
		}
		_sprite = sprite;
		_manageImg = manage;
	}
	void Image::SetAsNativeSize()
	{
		if (_sprite) {
			_lRect.w = _sprite->w();
			_lRect.h = _sprite->h();
			CalcWorldRect();
		}
	}
	void Image::Draw()
	{
		if (_sprite)
			MyGfx::Instance()->DrawCommand(_sprite, _wRect.x, _wRect.y, _wRect.w, _wRect.h, MyGfx::Layer::GUI);
	}
	bool Image::HasSprite()
	{
		return _sprite!=nullptr;
	}
}