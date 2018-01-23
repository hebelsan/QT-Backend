#include "PipeControl.hpp"

using namespace std;

PipeControl* PipeControl::getInstance()
{
	static PipeControl theInstance(3);
	return &theInstance;
}

PipeControl::PipeControl(int size)
{
	this->size = size;
	ringbuffer = new string[size];
	bottom = top = amount = 0;
}

void PipeControl::add(const string & msg)
{
	lock.lock();
	*(ringbuffer+top) = msg;
	increment(top);
	++amount;
	lock.unlock();
	if(amount == size)
		popAll();
}

void PipeControl::increment(int& x)
{
	x = (x+1) % size;
}

void PipeControl::pop()
{
	lock.lock();
	if(amount > 0)
	{
		cout << *(ringbuffer+bottom) << endl;
		increment(bottom);
		--amount;
	}
	lock.unlock();
}

void PipeControl::popAll()
{
	while(amount > 0)
	{
		pop();
	}
}
