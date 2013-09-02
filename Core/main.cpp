#include <Windows.h>
#include "Containers\List.h"
#include "String\StringPool.h"
#include "Debug\Console.hpp"
#include "FileSystem\FileSystem.hpp"

#include "Base\Subsystem.hpp"
#include "Base\SubsystemBootstrap.hpp"

#include "Configuration\ConfigurationNode.h"
#include "Configuration\Configuration.h"

#include "Configuration\ConfigurationParser.h"

#include <stdio.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	Core::Configuration test;

	test.Import("e.cfg");

	Crude::String as = test.GetValue("Player.Name");

	Core::FileSystem TestSystem("test");

	TestSystem.CreateFileSystem();

	return 0;
}