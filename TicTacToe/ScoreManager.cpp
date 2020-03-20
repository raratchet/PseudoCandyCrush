#include "ScoreManager.h"

ScoreManager::ScoreManager()
{

}

void ScoreManager::ResetScore()
{
	score = 0;
}

int ScoreManager::GetScore()
{
	return score;
}

void ScoreManager::SetScore(int value)
{
	score = value;
}

void ScoreManager::AddScore(int combo)
{
	score += BASE * combo;

	if(combo > 3)
		for (int mult = 1; mult <= combo; mult++)
			score += BASE * mult;
}
