#include <iostream>
#include <memory>

enum class Request
{
	EASY,
	MEDIUM,
	HARD,
	INVALID
};

class Handler
{
public:
	virtual void handleRequest(Request req);
	virtual std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> handler);
	virtual ~Handler() = default;
private:
	std::shared_ptr<Handler> next;
};

class AutomaticHandler : public Handler
{
public:
	void handleRequest(Request req) override;
};

class RegularHandler : public Handler
{
public:
	void handleRequest(Request req) override;
};	

class SpecialHandler : public Handler
{
public:
	void handleRequest(Request req) override;
};

int main()
{
	auto ah = std::make_shared<AutomaticHandler>();
	auto rh = std::make_shared<RegularHandler>();
	auto sh = std::make_shared<SpecialHandler>();
	ah->setNext(rh)->setNext(sh);
	ah->handleRequest(Request::INVALID);
}

void Handler::handleRequest(Request req)
{
	if(next)
	{
		next->handleRequest(req);
	}
	else
	{
		std::puts("request not handled");
	}
}

std::shared_ptr<Handler> Handler::setNext(std::shared_ptr<Handler> handler)
{
	next = handler;
	return handler;
}

void AutomaticHandler::handleRequest(Request req)
{
	if(req == Request::EASY)
	{
		std::puts("Easy request handled automatically");
	}
	else
	{
		std::puts("Request can't be solved automatically");
		Handler::handleRequest(req);
	}
}

void RegularHandler::handleRequest(Request req)
{
	if(req == Request::MEDIUM)
	{
		std::puts("Medium request solved by a consultant");
	}
	else
	{
		std::puts("Request can't be solved by a consultant");
		Handler::handleRequest(req);
	}
}

void SpecialHandler::handleRequest(Request req)
{
	if(req == Request::HARD)
	{
		std::puts("Hard request solved by a professional");
	}
	else
	{
		std::puts("Request can't be solved by a professional");
		Handler::handleRequest(req);
	}
}
