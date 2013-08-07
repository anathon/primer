#pragma once

#include "Subsystem.hpp"

#include "Containers\List.h"

namespace Core {


	class SubsystemBootstrap {

	public:
		SubsystemBootstrap();
		~SubsystemBootstrap();

	public:
		void RegisterSubsystem(Subsystem* TargetSubsystem);

	public:
		bool Boot();
		bool Kill();

	private:
		Crude::List<Subsystem*>* StartupList;

	private:
		void Sort(Crude::List<Subsystem*>& TargetList);
	};

}