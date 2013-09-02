#pragma once

#include "String\String.h"

namespace Core {

	struct FileSystemJob {

	public:
		unsigned int JobID;
		unsigned int JobResult;
		unsigned int JobResultingMemorySize;
		char* JobResultingMemory;
		Crude::String FileName;
	};

}