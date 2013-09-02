#include "FileSystem.hpp"

namespace Core {

	FileSystem::FileSystem(Crude::String BaseFolderLocation) {
		this->m_SubsystemName		= Crude::String("FileSystem");
		this->m_StartupPriority		= 0;
		this->BaseFolderLocation	= BaseFolderLocation;
		this->EnableFileIO			= true;
		this->FileSystemJobsQueue	= new Crude::Que<FileSystemJob>();
		this->Mutex					= false;
	}

	FileSystem::~FileSystem() {

	}

	bool FileSystem::CreateFileSystem() {

		// Initalize Thread
		ReturnSystem* ReturnAddress = 0;
		ReturnAddress = (ReturnSystem*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ReturnSystem));
		ReturnAddress->Home = this;

		if (ReturnAddress == 0)
			return false;

		// Spin Up Thread
		ThreasHandle = CreateThread(NULL, 0, FileSystemThreadEntry, ReturnAddress, 0, &ThreadID);

		// Do Our Checks
		if (ThreasHandle == 0)
		{
			return false;
		}

	}

	DWORD WINAPI FileSystem::FileSystemThreadEntry(LPVOID lpParam) {

		ReturnSystem* ReturnAddress = (ReturnSystem*)lpParam;

		if (ReturnAddress == 0)
			return 1;

		while(ReturnAddress->Home->EnableFileIO)
		{
			// Sleep for a bit to slow down
			Sleep(2);

			// Check if we are doing anything with the queue and lock if we need
			if (ReturnAddress->Home->Mutex)
				continue;
			else
				ReturnAddress->Home->Mutex = true;

			// Check the queue
			if (ReturnAddress->Home->FileSystemJobsQueue->Size() != 0)
			{
				// Pop a job off the queue
				FileSystemJob* CurrentJob = ReturnAddress->Home->FileSystemJobsQueue->Pop();

				// Do the job

			}

			// Unlock the queue if it is locked by us
			ReturnAddress->Home->Mutex = false;
		}

		return 0;

	}

}