#include "FileSystem.hpp"
#include "..\Debug\Console.hpp"

namespace Core {

	Crude::List<Crude::String> FileSystem::getDependencyList() {
		Crude::List<Crude::String> ReturnList(2);
		ReturnList.Insert("DebugSystem");
		return ReturnList;
	}

	bool FileSystem::Startup() {
		return true;
	}

	void FileSystem::Shutdown() {
	}

	bool FileSystem::Poll() {
		return true;
	}

	void FileSystem::PullMessages(Crude::Que<Core::Message>& Messages) {
	}

	void FileSystem::ProcessMessage(Crude::Que<Core::Message> Messages) {
	}

	void FileSystem::onSystemDown(Subsystem& TargetSystem) {
	}

	void FileSystem::onSystemUp(Subsystem& TargetSystem) {
	}

}