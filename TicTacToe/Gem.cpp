#include "Gem.h"

Gem::Gem()
{
	type = '0';
	visited = false;
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