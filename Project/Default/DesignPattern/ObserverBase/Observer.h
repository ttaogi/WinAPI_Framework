#pragma once

#include "Utility/Enums/Enums.h"

class Subject;

class Observer
{
private:
protected:
public:
	Observer() { }
	virtual ~Observer() { }

	virtual void OnNotify(Subject* _subject, EVENT _event) = 0;
};
