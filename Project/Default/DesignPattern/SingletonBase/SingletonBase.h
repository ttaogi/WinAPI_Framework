#pragma once

template<typename T>
class SingletonBase
{
protected:
	static T* instance;
	SingletonBase() {}
	virtual ~SingletonBase() {}
public:
	static T* GetSingleton()
	{
		if (!instance) instance = new T();
		return instance;
	}
	static void ReleaseSingleton()
	{
		if (instance) delete instance;
		instance = NULL;
	}
};

template<typename T>
T* SingletonBase<T>::instance = NULL;