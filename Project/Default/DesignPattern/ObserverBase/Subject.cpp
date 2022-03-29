#include "Stdafx/stdafx.h"

#include "DesignPattern/ObserverBase/Subject.h"

void Subject::Notify(EVENT _event)
{
	for (auto iter = observerVec.begin(); iter != observerVec.end(); ++iter)
		(*iter)->OnNotify(this, _event);
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
