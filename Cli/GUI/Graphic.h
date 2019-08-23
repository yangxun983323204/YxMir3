// GUI元素基类
#pragma once
#include <list>
#include "../SDLInc.h"
#include "../MyGfx.h"

using std::list;

namespace YxGUI {

	class Graphic
	{
		friend class Canvas;
		friend class Selectable;
		friend class EventSystem;
	public:
		bool Visiable;
		bool HitTestTarget;// 是否参与点击检测

		Graphic();
		~Graphic();
		void SetLocalPos(int x, int y);
		void SetLocalSize(uint32_t w, uint32_t h);
		// 获取屏幕相对坐标
		SDL_Rect GetLocalRect();
		void AddChild(Graphic *g);
		void RemoveChild(Graphic *g);
		void InsertChild(Graphic *g,uint32_t idx);
		uint32_t GetIndexInParent();
		void SetIndexInParent(uint32_t idx);
		virtual void Draw()=0;
		virtual bool HitTest(SDL_Point *p);
		float GetLocalScaleX();
		void SetLocalScaleX(float sx);
		float GetLocalScaleY();
		void SetLocalScaleY(float sy);
	protected:
		Graphic *_parent;
		// 屏幕相对坐标
		SDL_Rect _lRect;
		// 屏幕绝对坐标
		SDL_Rect _wRect;
		bool _focus;
		list<Graphic*> _children;
		uint32_t _idxInParent;
		float _lScaleX;
		float _lScaleY;
		float _wScaleX;
		float _wScaleY;
	    // 计算屏幕绝对坐标
		void CalcWorldRect();
	private:
		bool _interactive;
	};
}

