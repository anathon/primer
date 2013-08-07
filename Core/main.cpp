#include <Windows.h>
#include "Containers\List.h"
#include "String\StringPool.h"
#include "Debug\Console.hpp"
#include "Base\Subsystem.hpp"
#include "Base\SubsystemBootstrap.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	//Crude::StringPool testPool;
	Core::Console* testConsole = new Core::Console();

	//testPool.InsertString("this is a test");
	//testPool.InsertString("hope this code works");

	Core::SubsystemBootstrap engineBoot;

	engineBoot.RegisterSubsystem(testConsole);

	bool StartupResult = engineBoot.Boot();

	return 0;
}