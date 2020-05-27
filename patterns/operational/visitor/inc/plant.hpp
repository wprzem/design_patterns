#pragma once

class Visitor;

class Plant
{
public:
	virtual void accept(Visitor& v) = 0;
	virtual ~Plant() = default;
};

class Carrot : public Plant
{
public:
	void accept(Visitor& v) override;
};	

class Apple : public Plant
{
public:
	void accept(Visitor& v) override;
};
