#include <iostream>
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

class AnimalDecorator : public Animal
{
public:
	AnimalDecorator(std::unique_ptr<Animal>&& ptr);
	void giveVoice() const override;
private:
	std::unique_ptr<Animal> anim;
};

class NiceAnimalDecorator : public AnimalDecorator 
{
public:
	NiceAnimalDecorator(std::unique_ptr<Animal>&& ptr);
	void giveVoice() const override;
private:
	void giveIntroduction() const;
};

void showAnimal(std::unique_ptr<Animal>&& ptr)
{
	std::puts("new animal");
	ptr->giveVoice();
}

int main()
{
	auto an = std::make_unique<NiceAnimalDecorator>(std::make_unique<Dog>());
	showAnimal(std::move(an));
}

void Dog::giveVoice() const
{
	std::puts("woof");
}

AnimalDecorator::AnimalDecorator(std::unique_ptr<Animal>&& ptr) : anim(std::move(ptr)) {}

void AnimalDecorator::giveVoice() const
{
	anim->giveVoice();
}

NiceAnimalDecorator::NiceAnimalDecorator(std::unique_ptr<Animal>&& ptr) : AnimalDecorator::AnimalDecorator(std::move(ptr)) {}

void NiceAnimalDecorator::giveVoice() const
{
	giveIntroduction();
	AnimalDecorator::giveVoice();
}	

void NiceAnimalDecorator::giveIntroduction() const
{
	std::puts("I'm a nice dog");
}

	

