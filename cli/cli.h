#include "core.h"
#include <string>
#include <iostream>

using Core::GameState;

#ifndef _WIN32
	#define RESET		"\033[0m"
	#define RED		"\033[31m"
	#define GREEN		"\033[32m"
	#define YELLOW		"\033[33m"
	#define BLUE            "\033[34m"
        #define PURPLE          "\033[35m"
        #define BOLD_WHITE      "\033[1;37m"
        #define CLEAR           std::system("clear")
#else
        #define RESET           ""
        #define RED             ""
        #define GREEN           ""
        #define YELLOW          ""
        #define BLUE            ""
        #define PURPLE          ""
        #define BOLD_WHITE      ""
        #define CLEAR           std::system("cls")
#endif

	
namespace CLI {

	void PrintInterface(GameState&);
        std::string GetDatabasePath(int, char* []);
	void ProcessInput(GameState&, const std::string&);
        void ProcessCommand(GameState&, const std::string&);
        void PrintHelpMessage();
	void ClearScreen();
       	void End(GameState&);
	std::string ReadDatabase(const std::string&);

}
