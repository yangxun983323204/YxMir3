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
		virtual void Draw();
	protected:
		Sprite *_sprite;
		bool _manageImg;
	};
}
