#pragma once

#include "..\Base\Subsystem.hpp"

#include "ConfigurationNode.h"
#include "Containers\HashMap.h"
#include "Containers\Que.h"
#include "String\Tokenizer.h"

#include "ConfigurationParser.h"

namespace Core {

	class Configuration : public Subsystem {

	public:
		Configuration();
		~Configuration();

	SUBSYSTEM_DEC

	public:
		bool Import(Crude::String FileName);
		bool Export();

	public:
		Crude::String GetValue(Crude::String GetKey);
		bool InsertValue(Crude::String Key, Crude::String Value);

	private:
		Crude::HashMap<ConfigurationNode>* Nodes;
		Crude::Que<Core::Message> Messages;
		Core::Message UpdateMessage;

	private:
		ConfigurationNode* CreateSubNode(ConfigurationNode* DestinationNode, Crude::String Key);
		bool CheckCombination(int Token, int pToken);

	private:
		bool AllowFileIO;
	};

}