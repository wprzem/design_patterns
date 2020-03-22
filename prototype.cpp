#include <iostream>
#include <memory>

class Animal
{
public:
	virtual void giveVoice() const = 0;
	virtual std::unique_ptr<Animal> clone() = 0;
	virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
	Dog() { std::puts("constructing dog"); }
	Dog(const Dog&) { std::puts("copy constructing dog"); }
	void giveVoice() const override;
	std::unique_ptr<Animal> clone() override;
	~Dog() { std::puts("destructing dog"); }
};

class Cat : public Animal
{
public:
	void giveVoice() const override;
	std::unique_ptr<Animal> clone() override;
};

class AnimalPrototypeFactory
{
public:
	AnimalPrototypeFactory(std::unique_ptr<Animal> ptr);
	virtual std::unique_ptr<Animal> makeAnimal() const;
private:
	std::unique_ptr<Animal> prototype;
};

int main()
{
	AnimalPrototypeFactory dpf(std::make_unique<Dog>());
	auto animal1 = dpf.makeAnimal();
	animal1->giveVoice();	

	AnimalPrototypeFactory cpf(std::make_unique<Cat>()); 
	auto animal2 = cpf.makeAnimal();
	animal2->giveVoice(); 
}

void Dog::giveVoice() const
{
	std::puts("woof");
}

std::unique_ptr<Animal> Dog::clone()
{
	return std::make_unique<Dog>(*this);
}

void Cat::giveVoice() const
{
	std::puts("meow");
}

std::unique_ptr<Animal> Cat::clone()
{
	return std::make_unique<Cat>(*this);
}

AnimalPrototypeFactory::AnimalPrototypeFactory(std::unique_ptr<Animal> ptr) : prototype(std::move(ptr)) {}

std::unique_ptr<Animal> AnimalPrototypeFactory::makeAnimal() const
{
	return prototype->clone();
}
