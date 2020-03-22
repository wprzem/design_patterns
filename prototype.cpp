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

template <typename T>
class PrototypeFactory
{
public:
	PrototypeFactory(std::unique_ptr<T> ptr);
	virtual std::unique_ptr<T> getPrototype() const;
private:
	std::unique_ptr<T> prototype;
};

int main()
{
	PrototypeFactory<Animal> dpf(std::make_unique<Dog>());
	auto animal1 = dpf.getPrototype();
	animal1->giveVoice();	

	PrototypeFactory<Animal> cpf(std::make_unique<Cat>()); 
	auto animal2 = cpf.getPrototype();
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

template <typename T>
PrototypeFactory<T>::PrototypeFactory(std::unique_ptr<T> ptr) : prototype(std::move(ptr)) {}

template <typename T>
std::unique_ptr<T> PrototypeFactory<T>::getPrototype() const
{
	return prototype->clone();
}
