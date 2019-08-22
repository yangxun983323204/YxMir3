#pragma once
#include <stdint.h>
#include <functional>
#include "../SDLInc.h"

namespace YxGUI {
	class ClickDetector
	{
	public:
		std::function<void(uint8_t)> onClick;
		ClickDetector();
		~ClickDetector();
		void Down(uint8_t idx, int x,int y);
		void Up(uint8_t idx, int x, int y);
	private:
		SDL_Point _status[3];
	};

	inline ClickDetector::ClickDetector()
	{
	}

	inline ClickDetector::~ClickDetector()
	{
	}
	inline void ClickDetector::Down(uint8_t idx, int x, int y)
	{
		_status[idx] = { x,y };
	}
	inline void ClickDetector::Up(uint8_t idx, int x, int y)
	{
		if (abs(x-_status[idx].x)<10 && abs(y - _status[idx].y)<10)
		{
			if (onClick)
				onClick(idx);
		}
		_status[idx] = { 0,0 };
	}
}