#pragma once
#include "Board.h"
#include <vector>
#include "Gem.h"
class PowerUp
{
public:

	static void Bomb(int x, int y, int radius, Board* gBoard)
	{
		std::vector<Gem*> tmp = gBoard->GetGemsInRadius<std::vector<Gem*>>(x, y, radius);
		gBoard->DestoyGems<std::vector<Gem*>>(&tmp);
	}
};

