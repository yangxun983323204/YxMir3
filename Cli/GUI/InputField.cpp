#include "InputField.h"
#include "../SpriteMgr.h"
#include "../Utils.h"

namespace YxGUI {

	InputField::InputField()
	{
		_bg = new Image();
		AddChild(_bg);
		_bg->HitTestTarget = false;

		_text = new Text();
		AddChild(_text);
		_text->SetAutoSize(true);
		_text->HitTestTarget = false;
		IsPassword = false;

		_cursor = new Image();
		AddChild(_cursor);
		_cursor->SetSprite(SpriteMgr::Instance()->GetBuiltinSprite(SpriteMgr::IdxBuiltinVLine), false);
		_cursor->SetAsNativeSize();
		_cursor->HitTestTarget = false;
		_cursor->Visiable = false;

		_twinkleSpanFrame = 60;
		_currentFrame = 0;
		MaxChar = 20;
	}

	InputField::~InputField()
	{
	}
	void InputField::SetBackground(Sprite *sp,bool manageSp)
	{
		_bg->SetSprite(sp, manageSp);
	}
	void InputField::SetAsBgSize()
	{
		auto rect = _bg->GetLocalRect();
		SetLocalSize(rect.w, rect.h);
	}
	wstring InputField::GetText()
	{
		return _str;
	}
	void InputField::SetText(wstring str)
	{
		_str = str;
		if (IsPassword) {
			auto len = _str.length();
			wchar_t *star = new wchar_t[len+1];
			star[len] = '\0';
			for (size_t i = 0; i < len; i++)
			{
				star[i] = '*';
			}
			wstring strStar = star;
			_text->SetString(strStar);
		}
		else
			_text->SetString(str);
		_cursor->SetLocalPos(_text->GetLocalRect().w, 0);
	}
	void InputField::Draw()
	{
		if (_focus)
		{
			_currentFrame++;
			if (_currentFrame >= _twinkleSpanFrame) {
				_currentFrame = 0;
				_cursor->Visiable = !_cursor->Visiable;
			}
		}
	}
	bool InputField::HandleEvent(SDL_Event & e)
	{
		//Special key input
		if (e.type == SDL_KEYDOWN)
		{
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && _str.length() > 0)
			{
				//lop off character
				_str.pop_back();
				SetText(_str);
				goto TRUE;
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(YxUtils::Wstr2Str(_str).c_str());
				goto TRUE;
			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				auto chars = SDL_GetClipboardText();
				_str = YxUtils::Str2Wstr(chars);
				if (_str.length() > MaxChar)
					_str = _str.substr(0, MaxChar);
				SDL_free(chars);
				SetText(_str);
				goto TRUE;
			}
		}
		//Special text input event
		else if (e.type == SDL_TEXTINPUT)
		{
			//Not copy or pasting
			if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
			{
				//Append character
				_str += YxUtils::Str2Wstr(e.text.text);
				if (_str.length() > MaxChar)
					_str = _str.substr(0, MaxChar);
				SetText(_str);
				goto TRUE;
			}
		}

		return false;
	TRUE:
		return true;
	}
	void InputField::OnFocus(bool f)
	{
		_focus = f;
		_cursor->Visiable = f;
		if (f)
		{
			SDL_StartTextInput();
		}
		else {
			SDL_StopTextInput();
		}
	}
}