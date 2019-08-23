#include "InputField.h"

namespace YxGUI {

	InputField::InputField()
	{
		_bg = new Image();
		AddChild(_bg);
		_cursor = new Image();
		AddChild(_cursor);
		_text = new Text();
		AddChild(_text);
		_text->SetAutoSize(true);
		IsPassword = false;
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
			wchar_t *star = new wchar_t[len] {L'*'};
			wstring strStar = star;
			_text->SetString(strStar);
		}
		else
			_text->SetString(str);
		_cursor->SetLocalPos(_text->GetLocalRect().x, 0);
	}
	void InputField::Draw()
	{
		_cursor->Visiable = _focus;
	}
	bool InputField::HandleEvent(SDL_Event & e)
	{
		return false;
	}
	void InputField::OnFocus(bool f)
	{
		_focus = f;
	}
}