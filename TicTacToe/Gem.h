#pragma once
class Gem
{
private:
	int x, y;
	char type;
	bool visited;

public:

	Gem();
	
	bool operator==(Gem gem);

	void SetPos(int, int);

	int GetX();

	int GetY();
	
	char GetType();

	void SetType(char);
	
	bool Visited();
	
	void SetVisited(bool);

	//Swap type de dos gemas
	void operator>>(Gem* gem);

	bool Contiguous(Gem gem);

	void GenerateNewType();

};

