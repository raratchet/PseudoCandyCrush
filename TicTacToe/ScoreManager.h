#pragma once
class ScoreManager
{
private:
	const int BASE = 300;
	int score = 0;

public:

	ScoreManager();

	void ResetScore();

	int GetScore();

	void SetScore(int);

	void AddScore(int);
};    

