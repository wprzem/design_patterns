#include <iostream>
#include <array>
#include <optional>
#include <memory>
#include <algorithm>

static const int numLottoNumbers = 6;
using lottoResult = std::array<int, numLottoNumbers>;
lottoResult todaysResult = {1, 2, 5, 10, 15, 27};

class Numbers
{
public:
	virtual void printResults() = 0;
	virtual ~Numbers() = default;
};

class LottoNumbers : public Numbers
{
public:
	LottoNumbers();
	void printResults() override;
	void populateResults();
protected:
	lottoResult nums;
};

class LottoNumbersProxy : public Numbers
{
public:
	void printResults() override;
protected:
	std::unique_ptr<LottoNumbers>& getNums();
private:
	std::optional<std::unique_ptr<LottoNumbers>> nums;
};

int main()
{
	std::unique_ptr<Numbers> nums = std::make_unique<LottoNumbersProxy>();
	std::puts("doing important stuff before generating numbers...");
	nums->printResults();
}

LottoNumbers::LottoNumbers()
{
	populateResults();
}

void LottoNumbers::printResults()
{
	std::for_each(nums.begin(), nums.end(), [](int x) { std::cout << x << '\n'; });
}

void LottoNumbers::populateResults()
{
	std::puts("taking a lot of time to generate...");
	nums = todaysResult;
}

void LottoNumbersProxy::printResults()
{
	getNums()->printResults();
}

std::unique_ptr<LottoNumbers>& LottoNumbersProxy::getNums()
{
	if(!nums)
	{
		nums = std::make_unique<LottoNumbers>();
	}
	return *nums;
}
