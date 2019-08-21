#pragma once
#include "Graphic.h"

namespace YxGUI {
	class Image:
		public Graphic
	{
	public:
		Image();
		~Image();
		void SetSprite(Sprite *sprite);
		void SetAsNativeSize();
		virtual void Draw();
	protected:
		Sprite *_sprite;
	};

	Image::Image()
	{
		_sprite = nullptr;
	}

	Image::~Image()
	{
	}
	inline void Image::SetSprite(Sprite * sprite)
	{
		_sprite = sprite;
	}
	inline void Image::SetAsNativeSize()
	{
		if (_sprite) {
			_rect.w = _sprite->w;
			_rect.h = _sprite->h;
		}
	}
	inline void Image::Draw()
	{
		// todo 计算相对坐标
		MyGfx::Instance()->DrawCommand(_sprite, _rect.x, _rect.y, MyGfx::Layer::GUI);
	}
}
