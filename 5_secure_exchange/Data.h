#pragma once
#include <mutex>

template <class T> class Data
{
private:
	T _data;
	std::mutex M;
public:
	Data(T value) : _data{ value } {};

	friend std::ostream& operator<<(std::ostream& str, Data& c)
	{
		return str << c._data;
	}

/**
* Обработка двойной блокировки с помощью std::lock()
*/ 
	//friend void swap(Data& left, Data& right)
	//{
	//	if (&left == &right) return;
	//	std::lock(left.M, right.M);
	//	std::lock_guard<std::mutex>lock_left(left.M, std::adopt_lock);
	//	std::lock_guard<std::mutex>lock_right(right.M, std::adopt_lock);
	//	T change = left._data;
	//	left._data = right._data;
	//	right._data = change;
	//}

/**
* Обработка двойной блокировки с помощью std::scoped_lock()
*/
	//friend void swap(Data& left, Data& right)
	//{
	//	if (&left == &right) return;
	//	std::scoped_lock(left.M, right.M);
	//	T change = left._data;
	//	left._data = right._data;
	//	right._data = change;
	//}

/**
* Обработка двойной блокировки с помощью std::unique_lock()
*/
	friend void swap(Data& left, Data& right)
	{
		if (&left == &right) return;
		std::unique_lock lock_left(left.M, std::defer_lock);
		std::unique_lock lock_rightt(right.M, std::defer_lock);
		std::lock(lock_left, lock_rightt);
		T change = left._data;
		left._data = right._data;
		right._data = change;
	}
};

