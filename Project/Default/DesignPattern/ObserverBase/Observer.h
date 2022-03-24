#pragma once

class Observer
{
private:
protected:
public:
	Observer() { }
	virtual ~Observer() { }

	virtual void OnNotify() = 0;
};
