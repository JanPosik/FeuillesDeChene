#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include <vector>
#include "difficulty_types.h"
#include "word.h"
#include "game_state.h"

namespace Core {

	void Init(GameState&, const std::string&);
	void NextWord(GameState&);
	void PrintInterface(GameState&);
	void ProcessInput(GameState&, const std::string&);
	void ProcessCommand(GameState&, const std::string&);
	void CheckAnswer(GameState&, const std::string&);
	void PrintHelpMessage();
	std::string GetDatabasePath(int, char* []);
}

#endif
