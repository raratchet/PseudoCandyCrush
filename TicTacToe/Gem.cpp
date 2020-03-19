#include "Gem.h"
#include <iostream>
#include <ctime>

Gem::Gem()
{
	type = '0';
	visited = false;
	x = -1;
	y = -1;
}

void Gem::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Gem::GetX()
{
	return x;
}

int Gem::GetY()
{
	return y;
}

bool Gem::operator==(Gem gem)
{
	if (type == gem.GetType())
		return true;
	else
		return false;
}


char Gem::GetType()
{
	return type;
}

void Gem::SetType(char n_type)
{
	type = n_type;
}

bool Gem::Visited()
{
	return visited;
}

void Gem::SetVisited(bool state)
{
	visited = state;
}

void Gem::operator>>(Gem* gem)
{
	char tmp;
	tmp = type;
	SetType(gem->GetType());
	gem->SetType(tmp);
}

bool Gem::Contiguous(Gem gem)
{
	return 0;
}

void Gem::GenerateNewType()
{
	//srand(std::time(nullptr));
	int tmp = rand() % 4;

	switch (tmp)
	{
	case 0:
		type = 'r';
		break;
	case 1:
		type = 'v';
		break;
	case 2:
		type = 'a';
		break;
	case 3:
		type = 'b';
		break;
	default:
		type = '0';
		break;
	}
}
