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

//Compara si dos gemas son del mismo tipo
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

//Hace un swap de tipos entre dos gemas
void Gem::operator>>(Gem* gem)
{
	char tmp;
	tmp = type;
	SetType(gem->GetType());
	gem->SetType(tmp);
}

//Revisa si una gema esta contigua con otra
bool Gem::Contiguous(Gem gem)
{
	if(x + 1 == gem.GetX() && y == gem.GetY())
		return true;
	if (x - 1 == gem.GetX() && y == gem.GetY())
		return true;
	if (x == gem.GetX() && y + 1 == gem.GetY())
		return true;
	if (x == gem.GetX() && y - 1 == gem.GetY())
		return true;
	
	return false;
}

//Genera un nuevo tipo random para la gema
void Gem::GenerateNewType()
{
	//srand(std::time(nullptr));
	int tmp = rand() % 6;

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
	case 4:
		type = 'm';
		break;
	case 5:
		type = 'n';
		break;
	default:
		type = '0';
		break;
	}
}

