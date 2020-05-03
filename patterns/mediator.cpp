#include <iostream>
#include <memory>

class DamageMediator;

class Character
{
public:
	Character(DamageMediator* dm, int p, int hp) : dmgMediator(dm), power(p), health(hp) {}
	virtual void attack();
	virtual void getDmg(int dmg);
	virtual ~Character() = default;
	int getPower() const { return power; }
	int getHealthPoints() const { return health; }
private:
	DamageMediator* dmgMediator;
	int power; 
	int health;
};


class NormalCharacter : public Character
{
public:
	NormalCharacter(DamageMediator* dm) : Character(dm, NormalCharacter::p, NormalCharacter::hp) {}
private:
	static const int p = 2;
	static const int hp = 2;
};

class Enemy : public Character
{
public:
	Enemy(DamageMediator* dm) : Character(dm, Enemy::p, Enemy::hp) {}
private:
	static const int p = 5;
	static const int hp = 10;
};

class DamageMediator
{
public:
	DamageMediator();
	void processAttack(Character* ptr);
	Character& getMyChar() const;
	Character& getEnemy() const;
private:
	std::unique_ptr<Character> myChar;
	std::unique_ptr<Character> enemy;
};

int main()
{
	DamageMediator d;
	std::puts("MyChar attacking enemy");
	d.getMyChar().attack();

	std::puts("\nEnemy strikes back");	
	d.getEnemy().attack();
}

void Character::attack()
{
	dmgMediator->processAttack(this);
}

void Character::getDmg(int dmg)
{
	health -= dmg;
	if(health <= 0)
	{
		std::puts("I'm dead");
	}
	else
	{
		std::cout << "Remaining health: " << health << '\n';
	}
}

DamageMediator::DamageMediator() : myChar(std::make_unique<NormalCharacter>(this)), enemy(std::make_unique<Enemy>(this)) {}

void DamageMediator::processAttack(Character* ptr)
{
	auto power = ptr->getPower();

	if(ptr == myChar.get())
	{
		enemy->getDmg(power);
	}
	else if (ptr == enemy.get())
	{
		myChar->getDmg(power);
	}
}	

Character& DamageMediator::getMyChar() const
{
	return *myChar;
}

Character& DamageMediator::getEnemy() const
{
	return *enemy;
}
