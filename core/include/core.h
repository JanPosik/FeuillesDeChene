#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include "difficulty_types.h"
#include "word.h"
#include "word_loader.h"
#include "game_state.h"
#include "record_manager.h"

namespace Core {

	void NextWord(GameState&);
	bool CheckAnswer(GameState&, const std::string&);

}

#endif
