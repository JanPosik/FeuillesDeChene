#ifndef WORD_LOADER_H
#define WORD_LOADER_H

#include "game_state.h"
#include "load_result.h"
#include <string>


namespace Core {
	
	LOAD_RESULT LoadWords(GameState& state, const std::string&);

}

#endif
