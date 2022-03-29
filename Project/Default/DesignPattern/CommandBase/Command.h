#pragma once

class Command
{
private:
protected:
public:
	Command() { } 
	virtual ~Command() { }

	virtual void Execute(void* _p) = 0;
};
