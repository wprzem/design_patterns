#include <iostream>
#include <memory>

class FlowerState;

class Flower
{
public:
	Flower();
	void addWater();
	void dry();
private:
	friend class FlowerState;
	void changeState(std::unique_ptr<FlowerState>&& state);
	std::unique_ptr<FlowerState> fs;
};

class FlowerState
{
public:
	virtual void addWater(Flower& f) = 0;
	virtual void dry(Flower& f) = 0;
	void changeState(std::unique_ptr<FlowerState>&& state, Flower& f);
	virtual ~FlowerState() = default;
};

class DryFlowerState : public FlowerState
{
public:
	void addWater(Flower& f) override;
	void dry(Flower& f) override;
};

class SaturatedFlowerState : public FlowerState
{
public:
	void addWater(Flower& f) override;
	void dry(Flower& f) override;
};

class GoodFlowerState : public FlowerState
{
public:
	void addWater(Flower& f) override;
	void dry(Flower& f) override;
};

int main()
{
	Flower f;
	f.addWater();	
	f.addWater();
	f.addWater();
	f.dry();
	f.dry();
	f.dry();
	f.addWater();
	f.addWater();
}

Flower::Flower() : fs(std::make_unique<GoodFlowerState>()) {}

void Flower::addWater()
{
	fs->addWater(*this);
}

void Flower::dry()
{
	fs->dry(*this);
}

void Flower::changeState(std::unique_ptr<FlowerState>&& state)
{
	fs = std::move(state);
}

void FlowerState::changeState(std::unique_ptr<FlowerState>&& state, Flower& f)
{
	f.changeState(std::move(state));
}

void DryFlowerState::addWater(Flower& f)
{
	std::puts("added water - saved the flower");
	changeState(std::make_unique<GoodFlowerState>(), f);
}

void DryFlowerState::dry(Flower& f)
{	
	std::puts("can't dry, already dead");
}

void SaturatedFlowerState::addWater(Flower& f)
{
	std::puts("can't add water, already saturated");
}
	
void SaturatedFlowerState::dry(Flower& f)
{
	std::puts("dried - saved the flower");
	changeState(std::make_unique<GoodFlowerState>(), f);
}

void GoodFlowerState::addWater(Flower& f)
{
	std::puts("added water");
	changeState(std::make_unique<SaturatedFlowerState>(), f);
}

void GoodFlowerState::dry(Flower& f)
{
	std::puts("dried flower");
	changeState(std::make_unique<DryFlowerState>(), f);
}

