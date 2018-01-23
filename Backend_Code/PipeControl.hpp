#ifndef PipeControl_HPP
#define PipeControl_HPP

#include <string>
#include <iostream>
#include <mutex>

class PipeControl
{
private:
	PipeControl(int);
	std::mutex lock;
	std::string* ringbuffer;
	int bottom, top, size, amount;
	void pop();
	void increment(int &);
public:
	void add(const std::string &);
	void popAll();
	static PipeControl* getInstance();
};

#endif
