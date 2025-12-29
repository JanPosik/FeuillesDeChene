#include "core.h"
#include "init_windows_console.h"

int main(int argc, char* argv[])
{
	Core::GameState state;
	Core::CLI::PrintLoadResult(Core::Init(state, Core::CLI::GetDatabasePath(argc, argv)));
	Core::CLI::InitWindowsConsole();
	Core::CLI::ClearScreen();

	while(state.Play)
	{
		Core::NextWord(state);
		Core::CLI::PrintInterface(state);

		std::string userInput;
		std::getline(std::cin, userInput);

		Core::CLI::ProcessInput(state, userInput);
	}

	return 0;
}
