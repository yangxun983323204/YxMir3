// GUIԪ�ػ���
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
		bool HitTestTarget;// �Ƿ���������

		Graphic();
		~Graphic();
		void SetLocalPos(int x, int y);
		void SetLocalSize(uint32_t w, uint32_t h);
		// ��ȡ��Ļ�������
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
		// ��Ļ�������
		SDL_Rect _lRect;
		// ��Ļ��������
		SDL_Rect _wRect;
		bool _focus;
		list<Graphic*> _children;
		uint32_t _idxInParent;
		float _lScaleX;
		float _lScaleY;
		float _wScaleX;
		float _wScaleY;
	    // ������Ļ��������
		void CalcWorldRect();
	private:
		bool _interactive;
	};
}

