#include "core.h"
#include "word_loader.h"
#include <random>
#include <vector>
#include <string>
#include <cstdlib>

#ifndef _WIN32
	#define RESET		"\033[0m"
	#define RED		"\033[31m"
	#define GREEN 		"\033[32m"
	#define YELLOW		"\033[33m"
	#define BLUE		"\033[34m"
	#define PURPLE		"\033[35m"
	#define BOLD_WHITE	"\033[1;37m"
	#define CLEAR		std::system("clear")
#else
	#define RESET 		""
	#define RED	 	""
	#define GREEN		""
	#define YELLOW		""
	#define BLUE		""
	#define PURPLE		""
	#define BOLD_WHITE	""
	#define CLEAR		std::system("cls")
#endif

static std::random_device rd;

namespace Core {

	LOAD_RESULT Init(GameState& state, const std::string& filename)
	{
		return LoadWords(state, filename);
	}

	void NextWord(GameState& state)
	{
		std::mt19937 generator(rd());
		int last_index = static_cast<int>(state.Words.size() - 1);
		std::uniform_int_distribution<> distribution(0, last_index);
		
		int random_index = distribution(generator);

		if (!(state.Difficulty == DIFFICULTY::ANY))
		{
			while (state.Words[random_index].Difficulty != state.Difficulty)
			{
				random_index = distribution(generator);
			}
		}

		state.CurrentHint = state.Words[random_index].From;
		state.CurrentTarget = state.Words[random_index].To;	
	}

	bool CheckAnswer(GameState& state, const std::string& attempt)
	{
		if (state.CurrentTarget == attempt)
		{
			state.RightAnswer = RIGHT_ANSWER;
			state.Score++;
			state.Record = (state.Record < state.Score) ? state.Score : state.Record;
			return true;
		}
		else
		{
			state.RightAnswer = WRONG_ANSWER;
			state.Score = 0;
			return false;
		}
	}



	namespace CLI {

		void PrintInterface(GameState& state)
		{
			std::string bar = "";
			float p = 0;
	
			if (state.Record > 0)
				p = (float)state.Score / (float)state.Record;
	
			int p10 = (int)(p*10);
	
			for (int i = 0; i < p10; i++)
				bar.append("#");
			for (int i = 0; i < (10 - p10); i++)
				bar.append(" ");
	
			std::string score_text = ((state.RightAnswer == NO_ANSWER) ? "" : ((state.RightAnswer == RIGHT_ANSWER) ? GREEN : RED)) + std::string("Score: ") + std::to_string(state.Score) + RESET;
			std::string record_text = (state.Score >= state.Record && state.Record != 0) ? (YELLOW + std::string("Record: ") + std::to_string(state.Record) + RESET) : ("Record: " + std::to_string(state.Record));
			std::string difficulty_text_hard = (state.Difficulty == DIFFICULTY::HARD) ? (BOLD_WHITE + std::string("Hard: ")) : "";	
			std::string difficulty_text = (state.Difficulty == DIFFICULTY::MEDIUM) ? "Medium" : ((state.Difficulty == DIFFICULTY::EASY) ? "Easy" : "");
			std::string difficulty_text_any = (state.Difficulty == DIFFICULTY::ANY) ? "Any" : "";
	
			std::cout << "#-- " << score_text << " --- " << record_text << " --- Difficulty: "
				<< difficulty_text_hard << difficulty_text << difficulty_text_any << RESET << " --- " << BLUE << "[" << bar << "] " << (int)(p*100) << "%" << RESET
				<< "\n\\_ (" << state.LangFrom << ") " << state.CurrentHint << " = (" << state.LangTo << ") ";
		}
	
		std::string GetDatabasePath(int argc, char* argv[])
		{
			for (int i = 1; i < argc - 1; i++)
			{
				if (argv[i] == std::string("-d"))
					return argv[i + 1];
			}
			return "../data/en_fr.txt";
		}


		void ProcessInput(GameState& state, const std::string& input)
		{
			if (input[0] == '#')
			{
				ProcessCommand(state, input);
			}
			else
			{
				bool answer = CheckAnswer(state, input);

				if (answer)
				{
					ClearScreen();
				}
				else
				{
					std::cout << " \\_ The right answer is: " << PURPLE << state.CurrentTarget << RESET
						<< "\n\n[Type anything to continue]: ";
					std::string temp;
					std::getline(std::cin, temp);
					ClearScreen();
				}
			}
		}

		void ProcessCommand(GameState& state, const std::string& command)
		{
			if (command.compare("#exit") == 0)
				state.Play = false;
			else if (command.compare("#easy") == 0)
				state.Difficulty = DIFFICULTY::EASY;
			else if (command.compare("#medium") == 0)
				state.Difficulty = DIFFICULTY::MEDIUM;
			else if (command.compare("#hard") == 0)
				state.Difficulty = DIFFICULTY::HARD;
			else if (command.compare("#any") == 0)
				state.Difficulty = DIFFICULTY::ANY;
			else if (command.compare("#help") == 0)
				PrintHelpMessage();
	
			ClearScreen();
		}		


		void PrintHelpMessage()
		{
			std::cout << "\n\nWith using # you can type some useful commands:\n"
				<< "-----------------------------------------------\n\n"
				<< "\t#exit\t\tcloses program\n"
				<< "\t#help\t\tthis message\n"
				<< "\t#easy\t\tfilter only easy difficulty\n"
				<< "\t#medium\t\tfilter only medium difficulty\n"
				<< "\t#hard\t\tfilter only hard difficulty\n"
				<< "\t#any\t\tno filter; every difficulty\n"
				<< "\t#\t\tskips current word\n"
				<< "\n[Type anything to continue]: ";
			std::string temp;
			std::getline(std::cin, temp);
			ClearScreen();
		}

		void ClearScreen()
		{
			CLEAR;
		}

		void PrintLoadResult(LOAD_RESULT result)
		{
			switch (result)
			{
				case LOAD_RESULT::NOT_FOUND:
					std::cerr << "ERROR: Database file could not be found\n"; break;
				case LOAD_RESULT::OK:
					std::cerr << "Database initiliaze successfuly\n"; break;
			}
		}

	}
}
