#include "core.h"

int main(int argc, char* argv[])
{
	Core::GameState state;
	Core::Init(state, Core::GetDatabasePath(argc, argv));

	while(state.Play)
	{
		Core::NextWord(state);
		Core::PrintInterface(state);

		std::string userInput;
		std::getline(std::cin, userInput);

		Core::ProcessInput(state, userInput);
	}

	return 0;
}
