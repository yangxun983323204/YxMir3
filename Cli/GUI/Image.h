#pragma once
#include "Graphic.h"

namespace YxGUI {
	class Image:
		public Graphic
	{
	public:
		Image();
		~Image();
		void SetSprite(Sprite *sprite,bool manage);
		void SetAsNativeSize();
		void SetColor(MyColor col);
		MyColor GetColor();
		virtual void Draw();
		bool HasSprite();
	protected:
		Sprite *_sprite;
		bool _manageImg;
	};
}
