#include <iostream>
#include <string>
#include <algorithm>

class Printer
{
public:
	virtual void print() const;
	virtual ~Printer() = default;
};

class StringPrinter : public Printer
{
public:
	StringPrinter(std::string str);
	void print() const override;
private:
	std::string s;
};


int main()
{
	StringPrinter sp("hello");
	sp.print();
}

void Printer::print() const
{
	std::puts("yeoyooye");
}

StringPrinter::StringPrinter(std::string str) : s(std::move(str))
{

}

void StringPrinter::print() const
{
	std::for_each(s.begin(), s.end(), [](auto & letter){ std::cout << letter << '\n'; });
}
