#include <iostream>
#include <vector>
#include <memory>

class Animal
{
public:
	virtual void giveVoice() const;
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
	virtual std::unique_ptr<Animal> createAnimal();
	void addAnimal();
	void show() const;
private:
	std::vector<std::unique_ptr<Animal>> animals;	
};

class DogFactory : public AnimalFactory
{
public:
	std::unique_ptr<Animal> createAnimal() override;
};	

class CatFactory : public AnimalFactory
{
public:
	std::unique_ptr<Animal> createAnimal() override;
};

int main()
{
	DogFactory df;
	df.addAnimal();
	df.show();

	CatFactory cf;
	cf.addAnimal();
	cf.addAnimal();
	cf.show();
}

void Animal::giveVoice() const
{
	std::puts("I'm unknown animal");
}

void Dog::giveVoice() const
{
	std::puts("woof");
}

void Cat::giveVoice() const
{
	std::puts("meow");
}

std::unique_ptr<Animal> AnimalFactory::createAnimal()
{
	return std::make_unique<Animal>();
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

std::unique_ptr<Animal> DogFactory::createAnimal()
{
	return std::make_unique<Dog>();
}

std::unique_ptr<Animal> CatFactory::createAnimal()
{
	return std::make_unique<Cat>();
}
