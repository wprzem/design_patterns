#include <iostream>
#include <memory>
#include <vector>

class Story
{
public:
	virtual void tell() const = 0;
	virtual ~Story() = default;
};

class ScaryStory : public Story
{
public:
	void tell() const override;
};

class NiceStory : public Story
{
public:
	void tell() const override;
};
	
class StoryFactory
{
public:
	virtual std::unique_ptr<Story> createStory() = 0;
	virtual ~StoryFactory() = default;
};

class ScaryStoryFactory : public StoryFactory
{
public:
	std::unique_ptr<Story> createStory() override;
};

class NiceStoryFactory : public StoryFactory
{
public:
	std::unique_ptr<Story> createStory() override;
};

class StoryTeller
{
public:
	void tellAll() const;
	void addStory(StoryFactory& sf);
private:
	std::vector<std::unique_ptr<Story>> stories;
};

int main()
{
	StoryTeller st;
	ScaryStoryFactory ssf;
	NiceStoryFactory nsf;

	st.addStory(ssf);
	st.addStory(nsf);
	st.tellAll();
}

void ScaryStory::tell() const
{
	std::puts("veeery scary story");
}

void NiceStory::tell() const
{
	std::puts("nice story :)");
}

std::unique_ptr<Story> ScaryStoryFactory::createStory()
{
	return std::make_unique<ScaryStory>();
}

std::unique_ptr<Story> NiceStoryFactory::createStory()
{
	return std::make_unique<NiceStory>();
}

void StoryTeller::tellAll() const
{
	std::puts("long time ago...");
	for(auto& story : stories)
	{
		story->tell();
	}
}

void StoryTeller::addStory(StoryFactory& sf)
{
	stories.emplace_back(sf.createStory());
}
