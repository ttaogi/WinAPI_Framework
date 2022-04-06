#pragma once

#include "DesignPattern/ObserverBase/Observer.h"

class Subject
{
private:
protected:
	std::vector<Observer*> observerVec;
	void Notify(EVENT _event);
public:
	Subject() { }
	virtual ~Subject() { }

	void AddObserver(Observer* _observer);
	void RemoveObserver(Observer* _observer);
};