#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>
#include "difficulty_types.h"
#include "word.h"

#define WRONG_ANSWER	0
#define RIGHT_ANSWER	1
#define NO_ANSWER	2

namespace Core {

	struct GameState {
                int Score = 0;
                int Record = 0;
                int RightAnswer = NO_ANSWER;
                std::string CurrentHint;
                std::string CurrentTarget;
                std::string LangFrom;
                std::string LangTo;
                DIFFICULTY Difficulty = DIFFICULTY::ANY;
                bool Play = true;
		bool Flipped = false;
                std::vector<Word> Words;
        };

}


#endif
