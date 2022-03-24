#include "Stdafx/stdafx.h"

#include "DesignPattern/ObserverBase/Subject.h"

void Subject::Notify()
{
	for (auto iter = observerVec.begin(); iter != observerVec.end(); ++iter)
		(*iter)->OnNotify();
}

void Subject::AddObserver(Observer* _observer)
{
	observerVec.push_back(_observer);
}

void Subject::RemoveObserver(Observer* _observer)
{
	for (auto iter = observerVec.begin(); iter != observerVec.end(); ++iter)
		if ((*iter) == _observer)
			observerVec.erase(iter);
}
