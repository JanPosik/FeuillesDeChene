#include "core.h"
#include <random>
#include <vector>
#include <string>
#include <cstdlib>

static std::random_device rd;

namespace Core {

	void LoadDatabase(GameState& state, const std::string& filename)
	{
		LoadWords(state, filename);
	}

	void NextWord(GameState& state)
	{
		std::mt19937 generator(rd());
		int last_index = static_cast<int>(state.Words.size() - 1);
		std::uniform_int_distribution<> distribution(0, last_index);
		
		int random_index = distribution(generator);

		if (!(state.Difficulty == DIFFICULTY::ANY))
			while (state.Words[random_index].Difficulty != state.Difficulty)
				random_index = distribution(generator);

		if (!state.Flipped)
		{
			state.CurrentHint = state.Words[random_index].From;
			state.CurrentTarget = state.Words[random_index].To;	
		}
		else
		{
			state.CurrentHint = state.Words[random_index].To;
			state.CurrentTarget = state.Words[random_index].From;
		}
	}

	bool CheckAnswer(GameState& state, const std::string& attempt)
	{
		if (state.CurrentTarget == attempt)
		{
			state.RightAnswer = RIGHT_ANSWER;
			state.Score++;
			state.Record = (state.Record < state.Score) ? state.Score : state.Record;
			return true;
		}
		else
		{
			state.RightAnswer = WRONG_ANSWER;
			state.Score = 0;
			return false;
		}
	}

}
