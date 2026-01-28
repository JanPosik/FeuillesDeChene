#include <emscripten/emscripten.h>
#include <string>
#include "core.h"

#define EXPORT EMSCRIPTEN_KEEPALIVE

static Core::GameState g_state;

extern "C" {

EXPORT
bool loadDatabaseFromText(const char* text) {
    Core::LoadDatabase(g_state, text);
    return g_state.WordsLoaded;
}

EXPORT
const char* getLangFromHint() { return g_state.LangFrom.c_str(); }

EXPORT
const char* getLangToHint() { return g_state.LangTo.c_str(); }

EXPORT
int getScore() { return g_state.Score; }

EXPORT
int getRecord() { return g_state.Record; }

EXPORT
const char* getNextWord() {
	Core::NextWord(g_state);
	return g_state.CurrentHint.c_str();
}

EXPORT
const char* getCurrentTarget() {
	return g_state.CurrentTarget.c_str();
}

EXPORT
bool checkAnswer(const char* input)
{
	std::string attempt(input);
	return Core::CheckAnswer(g_state, attempt);
}

EXPORT
void setDifficulty(const char* difficulty)
{
	if (std::string(difficulty) == "easy")
		g_state.Difficulty = DIFFICULTY::EASY;
	if (std::string(difficulty) == "medium")
		g_state.Difficulty = DIFFICULTY::MEDIUM;
	if (std::string(difficulty) == "hard")
		g_state.Difficulty = DIFFICULTY::HARD;
	if (std::string(difficulty) == "any")
		g_state.Difficulty = DIFFICULTY::ANY;
}

}
