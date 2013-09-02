#include "ConfigurationNode.h"

namespace Core {

	ConfigurationNode::ConfigurationNode(Crude::String Key, Crude::String Value) {
		this->NodeName = Key.Hash();
		this->Value = Value;
	}

	ConfigurationNode::~ConfigurationNode() {
	}

	bool ConfigurationNode::AddNode(Crude::String Key, Crude::String Value) {

		bool NodeAlreadyExists = false;

		if (HasChild(Key.Hash()))
			NodeAlreadyExists = true;

		if (NodeAlreadyExists)
		{
			ConfigurationNode* Node = GetChild(Key.Hash());
			Node->Value = Value;
		}

		else
		{
			ConfigurationNode* InsertNode = new ConfigurationNode(Key, Value);
			NodeChildren.Insert(InsertNode);
		}

		return NodeAlreadyExists;
	}

	bool ConfigurationNode::IsLeaf() {
		if (NodeChildren.Size() == 0)
			return true;
		return false;
	}

	bool ConfigurationNode::IsKey(Crude::String Key) {
		if (NodeName == Key.Hash())
			return true;
		return false;
	}

	Crude::List<ConfigurationNode*> ConfigurationNode::GetChildren() {
		return NodeChildren;
	}

	Crude::String ConfigurationNode::GetValue() {
		return Value;
	}

	void ConfigurationNode::SetValue(Crude::String Value) {
		this->Value = Value;
	}

	bool ConfigurationNode::HasChild(__int64 Key) {

		for (unsigned int i = 0; i < NodeChildren.Size(); i++)
		{
			if (NodeChildren.At(i)->NodeName == Key)
				return true;
		}

		return false;

	}

	ConfigurationNode* ConfigurationNode::GetChild(__int64 Key) {

		if (HasChild(Key))
		{
			for (unsigned int i = 0; i < NodeChildren.Size(); i++)
			{
				if (NodeChildren.At(i)->NodeName == Key)
					return NodeChildren.At(i);
			}
		}

		return 0;
	}

}