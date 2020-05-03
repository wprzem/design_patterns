#include <iostream>
#include <array>
#include <memory>

template <typename In, typename Cont>
class Iterator
{
public:
	virtual void next() = 0;
	virtual In& getCurrent() = 0;	
	virtual ~Iterator() = default;
};

template <typename In, typename Cont>
class CircleIterator : public Iterator<In, Cont>
{
public:
	CircleIterator(Cont& cont) : container(cont), idx(0) {}
	void next() override;
	In& getCurrent() override;
private:
	Cont& container;
	size_t idx;
};

template <typename In, typename Cont>
class CircleTraverser 
{
public:
	CircleTraverser(Cont& cont) : iter(cont) {}
	template <typename F>
	void traverse(int x, F func);
private:
	CircleIterator<In, Cont> iter;
};

template <typename T, size_t Size>
class Collection
{
public:
	Collection(int multiplier);
	virtual std::unique_ptr<Iterator<T, Collection>> createIterator();
	virtual size_t size() { return Size; }
	virtual ~Collection() = default;
	T& operator[](int x) { return arr[x]; }
private:
	T arr[Size];
};

template <typename T, typename Cont> 
void showItems(Iterator<T, Cont>& iter, size_t times)
{
	for(size_t i = 0u; i < times; i++)
	{
		std::cout << iter.getCurrent() << '\n';
		iter.next();
	}
}

int main()
{
	Collection<int, 10> col(5);
	auto iter = col.createIterator();
	showItems(*iter, 20);
	std::puts("------Traverser------");
	CircleTraverser<int, Collection<int, 10>> ct(col);
	ct.traverse(5, [](auto x) { 
		static int num = 1;
		std::cout << "num " << num << ": " << x << '\n'; 
		num++;
		});	
}

template <typename In, typename Cont>
void CircleIterator<In, Cont>::next()
{
	if(++idx >= container.size())
	{
		idx = 0;
	}
}

template <typename In, typename Cont>
In& CircleIterator<In, Cont>::getCurrent()
{
	return container[idx];
}

template <typename In, typename Cont>
template <typename F>
void CircleTraverser<In, Cont>::traverse(int x, F func)
{
	for(int i = 0; i < x; i++)
	{
		func(iter.getCurrent());
		iter.next();
	}
}

template <typename T, size_t Size>
std::unique_ptr<Iterator<T, Collection<T, Size>>> Collection<T, Size>::createIterator()
{
	return std::make_unique<CircleIterator<T, Collection<T, Size>>>(*this);
}

template <typename T, size_t Size>
Collection<T, Size>::Collection(int multiplier)
{
	for(size_t i = 0; i < Size; i++)
	{
		arr[i] = i * multiplier;
	}
}

