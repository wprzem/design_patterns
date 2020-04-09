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

