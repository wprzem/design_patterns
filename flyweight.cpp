#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <utility>

class CarSharedStats
{
public:
	CarSharedStats(const std::string& b, const std::string& h) : brand(b), history(h) {}
	void show() const;
private:
	std::string brand;
	std::string history;
};

class CarUniqueStats
{
public:
	CarUniqueStats(const std::string& o) : owner(o) {}
	void show() const;
private:
	std::string owner;
};

class CarFlyweight
{
public:
	CarFlyweight(std::unique_ptr<CarSharedStats>&& ptr) : shStats(std::move(ptr)) {}
	void operation(std::unique_ptr<CarUniqueStats>&& uStats) const;
private:
	std::unique_ptr<CarSharedStats> shStats;
};

class CarFlyweightFactory
{
public:
	std::unique_ptr<CarFlyweight>& getCarFlyweight(const std::string& b);
	void addFlyweight(const std::string& brand, const std::string& history = "not much to be said");

private:
	std::unordered_map<std::string, std::unique_ptr<CarFlyweight>> brandLut;
};


void showRecord(CarFlyweightFactory& fact, const std::string& brand, const std::string& name)
{
	fact.getCarFlyweight(brand)->operation(std::make_unique<CarUniqueStats>(name));
}

int main()
{
	CarFlyweightFactory cff;
	cff.addFlyweight("Mercedes", "veeery long story");
	showRecord(cff, "Mercedes", "Mike");
	showRecord(cff, "Mercedes", "Jane");
	showRecord(cff, "Fiat", "Peter");
}		

void CarSharedStats::show() const
{
	std::cout << "brand: " << brand << '\n';
	std::cout << "brand history: " << history << '\n';
}

void CarUniqueStats::show() const
{
	std::cout << "owner: " << owner << "\n\n";
}

void CarFlyweight::operation(std::unique_ptr<CarUniqueStats>&& ptr) const
{
	shStats->show();
	ptr->show();	
}

std::unique_ptr<CarFlyweight>& CarFlyweightFactory::getCarFlyweight(const std::string& b)
{
	if(brandLut.find(b) == brandLut.end())
	{
		std::cout << "Creating default CarFlyweight for brand " << b << '\n';
		addFlyweight(b); 
	}
	return brandLut[b];	
}

void CarFlyweightFactory::addFlyweight(const std::string& brand, const std::string& history)
{
	auto cfptr = std::make_unique<CarSharedStats>(brand, history);
	brandLut[brand] = std::make_unique<CarFlyweight>(std::move(cfptr)); 
}

