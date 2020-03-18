#pragma once
class Gem
{
private:
	char type;
	bool visited;

public:

	Gem();
	
	bool operator==(Gem gem);
	
	char GetType();

	void SetType(char);
	
	bool Visited();
	
	void SetVisited(bool);

};

