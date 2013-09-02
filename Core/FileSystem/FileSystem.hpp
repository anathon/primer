#pragma once

#include <windows.h>

#include "Containers\Que.h"

#include "FileSystemJob.hpp"
#include "..\Base\Subsystem.hpp"

namespace Core {

	class FileSystem : public Subsystem {

	public:
		FileSystem(Crude::String BaseFolderLocation);
		~FileSystem();

	SUBSYSTEM_DEC

	public:
		bool CreateFileSystem();

	private:
		HANDLE ThreasHandle;
		DWORD ThreadID;
		Crude::String BaseFolderLocation;
		Crude::Que<FileSystemJob>* FileSystemJobsQueue;
		struct ReturnSystem { FileSystem* Home; };
		bool EnableFileIO;
		bool Mutex;

	private:
		static DWORD WINAPI FileSystemThreadEntry(LPVOID lpParam);

	};

}