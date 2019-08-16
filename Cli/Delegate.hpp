#pragma once
#include<list>
#include<functional>
#include<algorithm>

namespace Yx {
	template<class Cls, typename Ret, typename ...Args>
	class Binder
	{
	public:
		typedef Ret(Cls::*FuncType)(Args...);

		Binder(FuncType fun, Cls* class_ptr) :_func(fun), _classPtr(class_ptr) {}

		Ret operator()(Args&&...args)
		{
			return (_classPtr->*_func)(args...);
		}


		bool operator== (const Binder<Cls, Ret, Args...>&other) const
		{
			if (_classPtr == other._classPtr && _func == other._func)
				return true;
			return false;
		}

		template<typename T>
		bool operator==(const T&&)const
		{
			return false;
		}

	private:
		Cls*  _classPtr;
		FuncType _func;

	};

	template<typename ...T>
	class Delegate { };

	template<typename Ret, typename ...Args>
	class Delegate<Ret(Args...)>
	{
	public:
		typedef std::function<Ret(Args...)> Func;
		typedef std::list<Func> FuncList;
		typedef Ret(*RawFunc)(Args...);
		typedef Delegate<Ret(Args...)>  This;

		Delegate()
		{
		}

		~Delegate()
		{
			_funcList.clear();
		}


		This& operator -=(RawFunc func)
		{
			auto itr = std::find_if(_funcList.begin(), _funcList.end(),
				[&](Func&f)->bool
			{
				auto tmpfunc = f.target<Ret(*)(Args...)>();
				if (tmpfunc && *tmpfunc == func)
				{
					return true;
				}
				return false;
			});

			if (itr != _funcList.end())
				_funcList.erase(itr);

			return *this;
		}

		template<class Cls>
		This& operator -=(Binder<Cls, Ret, Args...>&& binder)
		{
			auto itr = std::find_if(_funcList.begin(), _funcList.end(),
				[&](Func&f)->bool
			{
				auto tmpfunc = f.target<Binder<Cls, Ret, Args...>>();
				if (tmpfunc && *tmpfunc == binder)
				{
					return true;
				}
				return false;
			});


			if (itr != _funcList.end())
			{
				_funcList.erase(itr);
			}
			return *this;
		}

		This& operator -=(Func func)
		{
			auto itr = std::find_if(_funcList.begin(), _funcList.end(),
				[&](Func&f)->bool
			{
				auto tmpfunc = f.target<Func>();
				if (tmpfunc && tmpfunc == &func)
				{
					return true;
				}
				return false;
			});

			if (itr != _funcList.end())
				_funcList.erase(itr);

			return *this;
		}

		This& operator +=(RawFunc func)
		{
			_funcList.push_back(func);
			return *this;
		}

		template<class Cls>
		This& operator +=(Binder<Cls, Ret, Args...>&& binder)
		{
			_funcList.push_back(binder);
			return *this;
		}

		This& operator +=(Func func)
		{
			_funcList.push_back(func);
			return *this;
		}

		//void operator()(Args&&...args)
		//{
		//	for (auto itr = _funcList.begin(); itr != _funcList.end(); itr++)
		//	{
		//		try
		//		{
		//			(*itr)(args...);
		//		}
		//		catch (std::exception ex)
		//		{
		//			//do something...
		//		}
		//	}
		//}

		void operator()(Args...args)
		{
			for (auto itr = _funcList.begin(); itr != _funcList.end(); itr++)
			{
				try
				{
					(*itr)(args...);
				}
				catch (std::exception ex)
				{
					//do something...
				}
			}
		}

		explicit operator bool() const
		{
			return (this->_funcList.size()>0);
		}

	private:
		FuncList _funcList;
	};


	template<typename Cls, typename Ret, typename ...Args>
	auto BindClassFunc(Ret(Cls::*FuncType)(Args...), Cls* class_ptr) ->Binder<Cls, Ret, Args...>
	{
		return Binder<Cls, Ret, Args...>(FuncType, class_ptr);
	}

};

