#include "core.h"
#include "cli.h"
#include "init_windows_console.h"
#include "cli_record_manager.h"

int main(int argc, char* argv[])
{
	Core::GameState state;
	CLI::RecordManager rm;

	Core::LoadDatabase(state, CLI::GetDatabasePath(argc, argv));
	CLI::InitWindowsConsole();
	CLI::ClearScreen();

	// load record and set it
	auto record = rm.Load();
	Core::ApplyRecord(state, record);

	while(state.Play && state.WordsLoaded)
	{
		Core::NextWord(state);
		CLI::PrintInterface(state);

		std::string userInput;
		std::getline(std::cin, userInput);

		CLI::ProcessInput(state, userInput);
	}

	// save new record, if exits
	record = Core::MakeRecord(state);
	rm.Save(record, (state.Record > state.LastRecord));

	CLI::End(state);

	return 0;
}
