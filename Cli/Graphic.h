// GUIÔªËØ»ùÀà
#pragma once
#include <list>
#include "SDLInc.h"
#include "MyGfx.h"

using std::list;

namespace YxGUI {

	class Graphic
	{
	public:
		Graphic();
		~Graphic();
		void SetRect(SDL_Rect &rect);
		SDL_Rect GetRect();
		void AddChild(Graphic *g);
		void RemoveChild(Graphic *g);
		void InsertChild(Graphic *g,uint32_t idx);
		uint32_t GetIndexInParent();
		void SetIndexInParent(uint32_t idx);
		virtual void Draw()=0;
		virtual bool HitTest(SDL_Point *p);
	protected:
		Graphic *_parent;
		SDL_Rect _rect;
		bool _focus;
		list<Graphic*> _children;
		uint32_t _idxInParent;
		float _scaleX;
		float _scaleY;
	};
}

