#pragma once
class TurnManager
{
private :
	short turnCount = 0;

public:

	TurnManager();

	void NextTurn();

	void Reset();

	short GetTurns();

	void SetTurns(short);
};

