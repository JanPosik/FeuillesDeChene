#include <vector>
#include <charconv>
#include "word_loader.h"
#include "difficulty_types.h"
#include "word.h"

// delete
#include <iostream>

static DIFFICULTY IntToDifficulty(int value)
{
	switch (value)
	{
		case 1: return DIFFICULTY::EASY;
		case 2: return DIFFICULTY::MEDIUM;
		case 3: return DIFFICULTY::HARD;
	}
	return DIFFICULTY::EASY;
}

namespace Core {

	void LoadDatabase(GameState& state, std::string_view text)
	{
		// set state attribute if other database was loaded and current one won't and clear vector
		state.Words.clear(); state.Words.shrink_to_fit();
		state.WordsLoaded = false;
		state.LangFrom = state.LangTo = "not loaded";

		size_t pos = 0;

		auto nextLine = [&](std::string_view& line) -> bool {
			if (pos >= text.size()) return false;
			size_t end = text.find('\n', pos);
			if (end == std::string_view::npos) end = text.size();
			line = text.substr(pos, end - pos);
			if (!line.empty() && line.back() == '\r') line.remove_suffix(1);
			pos = end + 1;
			return true;
		};

		std::string_view line;

		// check if database contains key
		if (!nextLine(line)) return;
		if (!(line == "@feuilles_de_chene")) return;

		// load language hints
		if (!nextLine(line)) return;
		size_t sep = line.find(';');
		if (sep != std::string_view::npos)
		{
			state.LangFrom = std::string(line.substr(0, sep));
			state.LangTo = std::string(line.substr(sep + 1));	
		}

		// words
		while (nextLine(line))
		{
			if (line.empty() || line[0] == '#') continue;

			size_t p1 = line.find(';');
			size_t p2 = line.find(';', p1 + 1);
			if (p1 == std::string_view::npos || p2 == std::string_view::npos) continue;

			std::string_view from = line.substr(0, p1);
			std::string_view to = line.substr(p1 + 1, p2 - p1 - 1);
			std::string_view diff = line.substr(p2 + 1);

			int difficulty = 1;
			auto res = std::from_chars(diff.data(), diff.data() + diff.size(), difficulty);

			Word word;
			word.From = std::string(from);
			word.To = std::string(to);
			word.Difficulty = IntToDifficulty(difficulty);

			state.Words.push_back(word);
		}

		state.WordsLoaded = (state.Words.size() > 0) ? true : false;
	}

}
