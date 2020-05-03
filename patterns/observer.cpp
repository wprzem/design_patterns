#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Observer;

class Subject
{
public:
	virtual void registerObserver(Observer* o);
	virtual void unregisterObserver(Observer* o);
	virtual void notify();
	virtual ~Subject() = default;
	virtual int getState() const { return state; }
	virtual void setState(int st);
private:
	std::vector<Observer*> observers;
	int state;
};

class Observer
{
public:
	Observer(Subject* s) : sbj(s) {}
	virtual void requestChange(int st);
	virtual void stateChanged();
	virtual ~Observer() = default;
private:
	Subject* sbj;
	int state;
};

int main()
{
	auto sub = std::make_unique<Subject>();	
	auto o1 = std::make_unique<Observer>(sub.get());
	auto o2 = std::make_unique<Observer>(sub.get());
	
	sub->registerObserver(o1.get());
	sub->registerObserver(o2.get());
	o1->requestChange(5);
}

void Subject::registerObserver(Observer* o)
{
	if(std::find(observers.begin(), observers.end(), o) == observers.end())
	{
		observers.push_back(o);
	}
	else
	{
		std::puts("observer already registered");
	}		
}

void Subject::unregisterObserver(Observer* o)
{
	auto pos = std::find(observers.begin(), observers.end(), o);
	if(pos != observers.end())
	{
		observers.erase(pos);
	}
	else
	{
		std::puts("observer unregister request invalid");
	}
}

void Subject::notify()
{
	for(auto& obs : observers)
	{
		obs->stateChanged();
	}	
}

void Subject::setState(int st)
{
	state = st;
	notify();
}

void Observer::requestChange(int st)
{
	sbj->setState(st);
}

void Observer::stateChanged()
{
	state = sbj->getState();
	std::cout << "state changed to " << state << '\n';
}
