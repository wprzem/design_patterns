#include <iostream>
#include <memory>

class Account
{
public:
	static Account& getInstance();
	void add(int x);
	void remove(int x);
	int getBalance() const;
private:
	Account() = default;
	int balance = 5;
};

int main()
{
	Account::getInstance().add(5);
	Account::getInstance().remove(3);
	std::cout << Account::getInstance().getBalance() << '\n';
}

int Account::getBalance() const
{
	return balance;
}

void Account::add(int x)
{
	balance += x;	
}

void Account::remove(int x)
{
	balance -= x;
}

Account& Account::getInstance()
{
	static Account instance;
	return instance;
}
	
