#include "record_manager.h"
#include <sstream>
#include <fstream>
#include <algorithm>

namespace Core {

	void LoadRecord(GameState& state)
	{
		std::ifstream file("../.feuilles_de_chene/record.txt");

		if (!file.is_open())
		{
			state.LastRecord = 0;
			return;
		}

		std::string line;
		int record;

		if (std::getline(file, line))
		{
			std::stringstream ss(line);
			try
			{
				state.LastRecord = std::stoi(line);
			}
			catch (const std::exception& e)
			{
				state.LastRecord = 0;
			}	
		}
		state.Record = state.LastRecord;
		file.close();
	}

	void WriteRecord(int new_record)
	{
		std::ofstream file("../.feuilles_de_chene/record.txt");

		if (file.is_open())
		{
			file << new_record << std::endl;
			file.close();
		}
	}

}
