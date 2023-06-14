#include "Observer.h"


void Observable::notify_all()
{
	for (auto observer : observers)
	{
		observer->update();
	}
}

void Observable::add_observer(Observer* observer)
{
	observers.push_back(observer);
}

void Observable::remove_observer(Observer* observer)
{
	for (int i = 0;i < observers.size(); i++)
	{
		if (observer == observers[i])
			observers.erase(observers.begin() + i);
	}
}