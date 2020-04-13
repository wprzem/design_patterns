#include <iostream>
#include <memory>
#include <string>

class ShopImpl
{
public:
	virtual void implMakeTransaction() const = 0;
	virtual ~ShopImpl() = default;
};

class Shop
{
public:
	Shop(std::unique_ptr<ShopImpl> ptr);
	virtual void makeTransaction() const;
	virtual ~Shop() = default;
protected:
	std::unique_ptr<ShopImpl> simpl;
};

class CandyShop : public Shop
{
public:
	CandyShop(std::unique_ptr<ShopImpl> ptr);
	void makeTransaction() const override;
private:
	std::string candyName = "caramel";
};

class CandyShopImpl : public ShopImpl
{
public:
	void implMakeTransaction() const override;
};

int main()
{
	auto cs = std::make_unique<CandyShop>(std::make_unique<CandyShopImpl>());
	cs->makeTransaction();
}

Shop::Shop(std::unique_ptr<ShopImpl> ptr) : simpl(std::move(ptr)) {}

void Shop::makeTransaction() const
{
	simpl->implMakeTransaction();
}

CandyShop::CandyShop(std::unique_ptr<ShopImpl> ptr) : Shop::Shop(std::move(ptr)) {}

void CandyShop::makeTransaction() const
{
	std::cout << "candy name: " << candyName << '\n';
	Shop::makeTransaction();
}

void CandyShopImpl::implMakeTransaction() const
{
	std::puts("giving away candies");
}


