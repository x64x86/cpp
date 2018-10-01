#include "pch.h"
#include <vector>
#include <iostream>
#include <memory>

class Broker
{
public:
	virtual void update(int) {};
};

class Exchange
{
public:
	Exchange() : stock_price{}, brokers{} {};
	void set_price(int price)
	{
		if (price > 0)
		{
			stock_price = price;
		}
		notify();
	}
	void attach_broker(Broker * broker)
	{
		brokers.push_back(broker);
	}
	void notify()
	{
		for (auto broker : brokers)
		{
			broker->update(stock_price);
		}
	}
private:
	int stock_price;
	std::vector<Broker *> brokers;
};

class HighBroker : public Broker
{
public:
	HighBroker(Exchange *exc, int threshold)
	{
		exc->attach_broker(this);
		high_threshold = threshold;
	}
	void update(int price)
	{
		if (price > high_threshold)
		{
			std::cout << "The price is higher than threshold, delta: " << price - high_threshold << std::endl;
		}
	}
private:
	int high_threshold{};
};

class LowBroker : public Broker
{
public:
	LowBroker(Exchange *exc, int threshold)
	{
		exc->attach_broker(this);
		low_threshold = threshold;
	}
	void update(int price)
	{
		if (price < low_threshold)
		{
			std::cout << "The price is lower than threshold, delta: " << low_threshold - price << std::endl;
		}
	}
private:
	int low_threshold{};
};

int main()
{
	int high_threshold{1000};
	int low_threshold{500};
	Exchange wallStreet;
	HighBroker Bob(&wallStreet, high_threshold);
	LowBroker Alice(&wallStreet, low_threshold);
	std::cout << "High threshold: " << high_threshold << " Low threshold: " << low_threshold << std::endl;
	int price = 700;
	while (price)
	{
		std::cout << "Set stock price (or 0 for exit): ";
		std::cin >> price;
		wallStreet.set_price(price);
	}
	return 0;
}
