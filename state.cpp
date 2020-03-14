#include <iostream>

class FlowerState;

class Flower
{
public:
	Flower();
	void addWater();
	void dry();
private:
	friend class FlowerState;
	void changeState(FlowerState* state);
	FlowerState* fs;
};

class FlowerState
{
public:
	virtual void addWater(Flower* f) = 0;
	virtual void dry(Flower* f) = 0;
	void changeState(FlowerState* state, Flower* f);
	virtual ~FlowerState() = default;
};

class DryFlowerState : public FlowerState
{
public:
	void addWater(Flower* f) override;
	void dry(Flower* f) override;
};

class SaturatedFlowerState : public FlowerState
{
public:
	void addWater(Flower* f) override;
	void dry(Flower* f) override;
};

class GoodFlowerState : public FlowerState
{
public:
	void addWater(Flower* f) override;
	void dry(Flower* f) override;
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

Flower::Flower() : fs(new GoodFlowerState) {}

void Flower::addWater()
{
	fs->addWater(this);
}

void Flower::dry()
{
	fs->dry(this);
}

void Flower::changeState(FlowerState* state)
{
	delete fs;
	fs = state;
}

void FlowerState::changeState(FlowerState* state, Flower* f)
{
	f->changeState(state);
}

void DryFlowerState::addWater(Flower* f)
{
	std::puts("added water - saved the flower");
	changeState(new GoodFlowerState, f);
}

void DryFlowerState::dry(Flower* f)
{	
	std::puts("can't dry, already dead");
}

void SaturatedFlowerState::addWater(Flower* f)
{
	std::puts("can't add water, already saturated");
}
	
void SaturatedFlowerState::dry(Flower* f)
{
	std::puts("dried - saved the flower");
	changeState(new GoodFlowerState, f);
}

void GoodFlowerState::addWater(Flower* f)
{
	std::puts("added water");
	changeState(new SaturatedFlowerState, f);
}

void GoodFlowerState::dry(Flower* f)
{
	std::puts("dried flower");
	changeState(new DryFlowerState, f);
}

