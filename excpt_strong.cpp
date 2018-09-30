#include "stdafx.h"
#include <memory>
#include <time.h>
#include <stdexcept>
#include <iostream>

enum Color {Red, Green, Blue};
enum Model {Mercedes, Toyota, BMW, VW};

struct Car
{
	Car(Model m, Color c) : model(m), color(c) {};
	Model model;
	Color color;
};

std::unique_ptr<Car> GenerateRandomCar()
{
	std::unique_ptr<Car> car{nullptr};
	try
	{
		Color color = Color(rand() % 3);
		Model model = Model(rand() % 4);
		car = std::make_unique<Car>(Car(model, color));
	}
	catch (const std::exception& except)
	{
		std::cout << except.what();
	}
	return car;
}

int main()
{
	srand(time(0));
	int cars{ 10 };
	for (int i{ 0 }; i < cars; ++i)
	{
		std::unique_ptr<Car> car = std::move(GenerateRandomCar());
		std::cout << "Model: " << car->model << " Color: " << car->color << std::endl;
	}
	std::cin.ignore();
	return 0;
}
