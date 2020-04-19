#include <iostream>
#include <vector>
#include <memory>

class StoryTeller
{
public:
	void tellStory() const;
	virtual void tellMainPlot() const = 0;
	virtual void tellIntroduction() const;
	virtual void tellSurprise() const {}
};

class ScaryStoryTeller : public StoryTeller
{
public:
	void tellMainPlot() const override;
	void tellSurprise() const override;
};

class LongStoryTeller : public StoryTeller
{
public:
	void tellMainPlot() const override;
	void tellIntroduction() const override;
};

class RegularStoryTeller : public StoryTeller
{
public:
	void tellMainPlot() const override;
};

void tellAll(const std::vector<std::unique_ptr<StoryTeller>>& st)
{
	for(auto& story : st)
	{
		story->tellStory();
		std::puts("");
	}
}

int main()
{
	std::vector<std::unique_ptr<StoryTeller>> stories;
	stories.emplace_back(std::make_unique<ScaryStoryTeller>());
	stories.emplace_back(std::make_unique<LongStoryTeller>());
	stories.emplace_back(std::make_unique<RegularStoryTeller>());
	tellAll(stories);
}

void StoryTeller::tellStory() const
{
	tellIntroduction();
	tellMainPlot();
	tellSurprise();
}

void StoryTeller::tellIntroduction() const
{
	std::puts("long time ago...");
}

void ScaryStoryTeller::tellMainPlot() const
{
	std::puts("main scary story plot");
}

void ScaryStoryTeller::tellSurprise() const
{
	std::puts("boo!");
}

void LongStoryTeller::tellMainPlot() const
{
	std::puts("main long story plot");
}

void LongStoryTeller::tellIntroduction() const
{
	std::puts("long time ago in long story...");
}

void RegularStoryTeller::tellMainPlot() const
{
	std::puts("regular story plot");
}
