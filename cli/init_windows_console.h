#ifndef INIT_WINDOWS_CONSOLE_H
#define INIT_WINDOWS_CONSOLE_H

#ifdef _WIN32
	#include <windows.h>
#endif

namespace CLI {

	void InitWindowsConsole()
	{
		#ifdef _WIN32
			SetConsoleOutputCP(CP_UTF8);
   			SetConsoleCP(CP_UTF8);
		#endif
	}

}

#endif
