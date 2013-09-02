#pragma once

#include "Containers\List.h"
#include "String\String.h"

namespace Core {

	class ConfigurationNode {
		
	public:
		ConfigurationNode(Crude::String Key, Crude::String Value);
		~ConfigurationNode();

	public:
		bool AddNode(Crude::String Key, Crude::String Value);
		bool IsLeaf();
		bool IsKey(Crude::String Key);
		Crude::List<ConfigurationNode*> GetChildren();
		Crude::String GetValue();
		void SetValue(Crude::String Value);

	public:
		Crude::String Value;

	private:
		__int64 NodeName;
		Crude::List<ConfigurationNode*> NodeChildren;

	private:
		bool HasChild(__int64 Key);
		ConfigurationNode* GetChild(__int64 Key);
	};

}