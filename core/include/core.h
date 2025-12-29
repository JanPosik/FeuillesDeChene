#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include <vector>
#include "difficulty_types.h"
#include "word.h"
#include "game_state.h"
#include "load_result.h"

namespace Core {

	LOAD_RESULT Init(GameState&, const std::string&);
	void NextWord(GameState&);
	bool CheckAnswer(GameState&, const std::string&);

	namespace CLI {

		void PrintInterface(GameState&);
		std::string GetDatabasePath(int, char* []);
		void ProcessInput(GameState&, const std::string&);
		void ProcessCommand(GameState&, const std::string&);
		void PrintHelpMessage();
		void ClearScreen();
		void PrintLoadResult(LOAD_RESULT);

	}
}

#endif
