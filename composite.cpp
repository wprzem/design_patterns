#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

class Species
{
public:
	Species(const std::string& n);
	virtual void showName() const;
	virtual void add(std::unique_ptr<Species>&& ptr) {}
	virtual ~Species() = default;
private:
	std::string name;
};

class GroupedSpecies : public Species
{
public:
	GroupedSpecies(const std::string& n);
	void showName() const override;
	void add(std::unique_ptr<Species>&& ptr) override;
private:
	std::vector<std::shared_ptr<Species>> group;
};

int main()
{
	auto allSpec = std::make_unique<GroupedSpecies>("All animals");
	allSpec->add(std::make_unique<Species>("Human"));
	auto mammals = std::make_unique<GroupedSpecies>("Mammals");
	mammals->add(std::make_unique<Species>("Bear"));
	mammals->add(std::make_unique<Species>("Snake"));

	allSpec->add(std::move(mammals));
	allSpec->showName();
}

Species::Species(const std::string& n) : name(n) {}

void Species::showName() const
{
	std::cout << name << '\n';
}

GroupedSpecies::GroupedSpecies(const std::string& n) : Species::Species(n) {}

void GroupedSpecies::showName() const
{
	std::for_each(group.begin(), group.end(), [](auto& s) { s->showName(); });
}

void GroupedSpecies::add(std::unique_ptr<Species>&& ptr)
{
	group.emplace_back(std::move(ptr));
}


