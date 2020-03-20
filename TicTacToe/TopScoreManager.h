#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
class TopScoreManager
{
private:
	const char* filePath = "path";
	std::ifstream* saveFile;
public:
	TopScoreManager();

	std::vector<std::string> ReadTopScores();
};

