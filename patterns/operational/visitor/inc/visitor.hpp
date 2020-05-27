#pragma once

class Carrot;
class Apple;

class Visitor
{
public:
	virtual void visit(Carrot& c) = 0;
	virtual void visit(Apple& a) = 0;
	virtual ~Visitor() = default;	
};

class PrintingVisitor : public Visitor
{
public:
	void visit(Carrot& c) override;
	void visit(Apple& a) override;	
};
