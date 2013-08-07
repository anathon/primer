#pragma once

#include "Message.h"

#include "String\String.h"
#include "Containers\List.h"
#include "Containers\Que.h"

#define SUBSYSTEM_DEC public: \
			Crude::List<Crude::String> getDependencyList(); \
			bool Startup(); \
			void Shutdown(); \
			bool Poll(); \
			void PullMessages(Crude::Que<Core::Message>& Messages); \
			void ProcessMessage(Crude::Que<Core::Message>& Messages); \
			void onSystemDown(Subsystem& TargetSystem); \
			void onSystemUp(Subsystem& TargetSystem);

namespace Core {

	class Subsystem {

	public:
		Subsystem() : m_SubsystemName(), m_StartupPriority(0) {}

	public:
		virtual Crude::List<Crude::String> getDependencyList() = 0;

	public:
		virtual bool Startup() = 0;
		virtual void Shutdown() = 0;

	public:
		virtual bool Poll() = 0;

	public:
		virtual void PullMessages(Crude::Que<Core::Message>& Messages) = 0;
		virtual void ProcessMessage(Crude::Que<Core::Message>& Messages) = 0;

	public:
		virtual void onSystemDown(Subsystem& TargetSystem) = 0;
		virtual void onSystemUp(Subsystem& TargetSystem) = 0;

	public:
		unsigned int GetPriority() {return m_StartupPriority;}
		Crude::String GetSubsystemName() {return m_SubsystemName;}

	protected:
		Crude::String m_SubsystemName;
		unsigned int m_StartupPriority;
	};

}