#include "TopScoreManager.h"

std::vector<std::string> TopScoreManager::ReadTopScores()
{
	if (saveFile == nullptr)
		saveFile = new std::ifstream(filePath);

	std::vector<std::string> topscores;

	std::string line;
	std::string delimiter = ";";
	if (saveFile->is_open())
	{
		while (std::getline(*saveFile,line))
		{
			try
			{
				topscores.push_back(line);
			}
			catch (...)
			{
				std::cout << "An error ocurred while reading File" << std::endl;
				return topscores;
			}
		}
		return topscores;
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return topscores;
	}

}
