#include "cli_record_manager.h"
#include <fstream>
#include <algorithm>

namespace CLI {

	Core::Record RecordManager::Load()
	{
		std::ifstream file("../data/records.txt");
		int record = 0;

		if (!file.is_open())
			record = 33;

		std::string line;
		if (getline(file, line))
		{
			try {
				record = std::stoi(line);
			} catch (const std::exception e) {}
		}

		return {record};
	}

	void RecordManager::Save(const Core::Record& record, bool save)
	{
		if (save)
		{
			std::ofstream file("../data/records.txt");
			file << record.Default << "\n";
			file.close();
		}
	}

}
