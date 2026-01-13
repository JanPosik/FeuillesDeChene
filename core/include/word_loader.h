#ifndef WORD_LOADER_H
#define WORD_LOADER_H

#include "game_state.h"
#include <string>
#include <string_view>

namespace Core {
	
	void LoadDatabase(GameState& state, std::string_view);

}

#endif
