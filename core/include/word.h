#ifndef WORD_H
#define WORD_H

#include <string>
#include "difficulty_types.h"

struct Word {
	std::string From;
	std::string To;
	DIFFICULTY Difficulty;
};

#endif
