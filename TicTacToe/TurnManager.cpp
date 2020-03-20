#include "TurnManager.h"

TurnManager::TurnManager()
{

}

void TurnManager::NextTurn()
{
	turnCount++;
}

void TurnManager::Reset()
{
	turnCount = 0;
}

short TurnManager::GetTurns()
{
	return turnCount;
}

void TurnManager::SetTurns(short value)
{
	turnCount = value;
}