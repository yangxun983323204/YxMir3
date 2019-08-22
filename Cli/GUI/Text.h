#pragma once
#include "Graphic.h"

namespace YxGUI {
	using std::wstring;

	class Text :
		public Graphic
	{
	public:
		Text();
		~Text();
		wstring GetString();
		void SetString(wstring str);
		bool GetAutoSize();
		void SetAutoSize(bool a);
		virtual void Draw();
	protected:
		wstring _str;
		bool _autoSize;
		Sprite *_sprite;// 管理生命周期
	};
}