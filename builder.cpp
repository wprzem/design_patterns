#include <iostream>
#include <vector>
#include <memory>

class DishBuilder;

class Dish
{
public:
	void addStep(const std::string& step);
	void showRecipe() const;
private:
	std::vector<std::string> recipe;
};

class Restaurant
{
public:
	void showMenu() const;
	void addDishToMenu(DishBuilder& db);
private:
	std::vector<std::unique_ptr<Dish>> menu;
};

class DishBuilder
{
public:
	virtual void createDish() = 0;
	virtual void addSetup() = 0;
	virtual void addCookingStep() = 0;
	virtual ~DishBuilder() = default;
	virtual std::unique_ptr<Dish> getResult() = 0;
};

class PizzaBuilder : public DishBuilder
{
public:
	void createDish() override;
	void addSetup() override;
	void addCookingStep() override;
	std::unique_ptr<Dish> getResult() override;
private:
	std::unique_ptr<Dish> dish;
};

int main()
{
	Restaurant rest;
	PizzaBuilder pizza;
	rest.addDishToMenu(pizza);
	rest.showMenu();
}

void Dish::addStep(const std::string& step)
{
	recipe.push_back(step);
}

void Dish::showRecipe() const
{
	for(auto& step : recipe)
	{
		std::cout << step << '\n';
	}
}

void Restaurant::showMenu() const
{
	int counter = 1;
	for(auto& pos : menu)
	{
		std::cout << "Position " << counter << ":\n";
		pos->showRecipe();
		counter++;
	}
}

void Restaurant::addDishToMenu(DishBuilder& db)
{
	db.createDish();
	db.addSetup();
	db.addCookingStep();
	menu.push_back(db.getResult());
}

void PizzaBuilder::createDish()
{
	dish = std::make_unique<Dish>();
}

void PizzaBuilder::addSetup()
{
	dish->addStep("Do nothing at setup");
}

void PizzaBuilder::addCookingStep()
{
	dish->addStep("Cook in oven");
	dish->addStep("Watch if it doesn't burn");
}

std::unique_ptr<Dish> PizzaBuilder::getResult()
{
	return std::move(dish);
}









