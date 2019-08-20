#pragma once

template <typename T>
class Singleton 
{
public:
	static T *Instance()
	{
		if (_inst == nullptr)
			_inst = new T();
		return _inst;
	}
	static void Destroy()
	{
		delete _inst;
		_inst = nullptr;
	}
private:
	static T *_inst;
};
template<typename T>
T *Singleton<T>::_inst = nullptr;
