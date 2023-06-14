#pragma once
#include <vector>
class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
private:

	std::vector<Observer*> observers;

protected:
	void notify_all();

public:
	void add_observer(Observer* observer);

	void remove_observer(Observer* observer);
};
