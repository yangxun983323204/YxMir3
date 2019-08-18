#pragma once
#include <string>
#include <codecvt>

using std::string;
using std::wstring;

class YxUtils 
{
public:
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	static string Wstr2Str(wstring wstr)
	{
		if (wstr.length() == 0)
			return "";
		string str = converter.to_bytes(wstr);
		return str;
	}

	static wstring Str2Wstr(string str)
	{
		if (str.length() == 0)
			return L"";
		wstring wstr = converter.from_bytes(str);
		return wstr;
	}
};