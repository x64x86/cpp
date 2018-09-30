#include "stdafx.h"
#include <memory>
#include <string>
#include <iostream>

class Egg
{
public:
	Egg(int w = 1): weight(w) {};
	int GetWeight() { return weight; }
private:
	int weight;
};

class Omelette
{
public:
	Omelette(): weight() {};
	void AddEgg(std::unique_ptr<Egg> egg)
	{
		weight += egg->GetWeight(); 
	};
	int CutPiece(int piece_weight)
	{
		int cut_piece{ piece_weight };
		if (piece_weight > weight)
		{
			std::cout << "A piece is larger than the omelette. Cut the rest of omelette" << std::endl;
			cut_piece = weight;
			weight = 0;
		}
		else
		{
			weight -= piece_weight;
		}
		return cut_piece;
	}
	int GetWeight() { return weight; }
private:
	int weight;
};

std::shared_ptr<Omelette> MakeOmelette(int eggs)
{
	std::shared_ptr<Omelette> omelette { new Omelette() };
	for (int i{ 0 }; i < eggs; ++i)
	{
		int weight = rand() % 10 + 100; //random weight of egg
		std::unique_ptr<Egg> egg{ new Egg(weight) };
		omelette->AddEgg(std::move(egg));
	}
	return omelette;
}

int EatOmelette(std::shared_ptr<Omelette> omelette)
{
	int piece = rand() % 100 + 200; //random piece to eat
	int cut_piece = omelette->CutPiece(piece);
	return cut_piece;
}

int main()
{
	int eaters{ 5 };
	int eggs{ 10 };
	std::shared_ptr<Omelette> omelette{ MakeOmelette(eggs) };
	std::cout << "Omelette is cooked. Weight: " << omelette->GetWeight() << std::endl;
	for (int eater = 0; eater < eaters; eater++)
	{
		std::cout << "Eater " << eater + 1 << " has eaten " << EatOmelette(omelette) << std::endl;
	}
	std::cin.ignore();
    return 0;
}
