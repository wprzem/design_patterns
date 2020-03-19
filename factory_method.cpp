#include <iostream>
#include <vector>
#include <memory>

class Animal
{
public:
	virtual void giveVoice() const = 0;
};

class Dog : public Animal
{
public:
	void giveVoice() const override;
};

class Cat : public Animal
{
public:
	void giveVoice() const override;
};


class AnimalFactory
{
public:
	virtual std::unique_ptr<Animal> createAnimal() = 0;
	void addAnimal(); 
	void show() const;
private:
	std::vector<std::unique_ptr<Animal>> animals;	
};

template <typename T>
class ConcreteAnimalFactory : public AnimalFactory
{
public:
	std::unique_ptr<Animal> createAnimal() override;
};

int main()
{
	ConcreteAnimalFactory<Dog> df;
	df.addAnimal();
	df.show();

	ConcreteAnimalFactory<Cat> cf;
	cf.addAnimal();
	cf.addAnimal();
	cf.show();
}

void Dog::giveVoice() const
{
	std::puts("woof");
}

void Cat::giveVoice() const
{
	std::puts("meow");
}

template <typename T>
std::unique_ptr<Animal> ConcreteAnimalFactory<T>::createAnimal()
{
	return std::make_unique<T>();
}

void AnimalFactory::show() const
{
	for(auto& animal : animals)
	{
		animal->giveVoice();
	}
}

void AnimalFactory::addAnimal()
{
	animals.push_back(createAnimal());
}

