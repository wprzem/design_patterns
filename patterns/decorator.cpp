#include <iostream>
#include <memory>

class Animal
{
public:
	virtual void giveVoice() const = 0; 
	virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
	void giveVoice() const override;
};

class AnimalDecorator : public Animal
{
public:
	AnimalDecorator(const Animal& a);
	void giveVoice() const override;
private:
	const Animal& anim;
};

class NiceAnimalDecorator : public AnimalDecorator 
{
public:
	NiceAnimalDecorator(const Animal& a);
	void giveVoice() const override;
private:
	void giveIntroduction() const;
};


int main()
{
	Dog d;
	const Animal& an = NiceAnimalDecorator(d);
	an.giveVoice();
}

void Dog::giveVoice() const
{
	std::puts("woof");
}

AnimalDecorator::AnimalDecorator(const Animal& a) : anim(a) {}

void AnimalDecorator::giveVoice() const
{
	anim.giveVoice();
}

NiceAnimalDecorator::NiceAnimalDecorator(const Animal& a) : AnimalDecorator::AnimalDecorator(a) {}

void NiceAnimalDecorator::giveVoice() const
{
	giveIntroduction();
	AnimalDecorator::giveVoice();
}	

void NiceAnimalDecorator::giveIntroduction() const
{
	std::puts("I'm a nice dog");
}

	

