#include "Configuration.h"
#include <Windows.h>

namespace Core {

	Configuration::Configuration() : Nodes(0), AllowFileIO(true) {

		Nodes = new Crude::HashMap<ConfigurationNode>(10);

	}

	Configuration::~Configuration() {

		delete Nodes;
		
	}

	bool Configuration::Import(Crude::String FileName) {

		FILE * Input;
		fopen_s(&Input, FileName.Data(), "r");

		if (Input == 0)
			return false;

		yyin = Input;

		int Token = 0, pToken = 0;
		int ComplexKeyC = 0;
		char Buffer[256];
		//Crude::String cBuffer;
		Crude::List<Crude::String> Keys;

		while (Token = yylex())
		{
			sprintf_s(Buffer, yytext);
			Crude::String* KeyInstance = new Crude::String(Buffer);

			if (!CheckCombination(Token, pToken))
				return false;

			if (Token == SECTIONSTART)
			{
				ComplexKeyC++;
			}

			if (Token == SECTIONEND)
			{
				ComplexKeyC--;
				Keys.Remove(ComplexKeyC);
			}

			if (Token == VALUE && pToken != ASSIGNMENT)
			{
				Keys.Insert(*KeyInstance);
			}

			if (pToken == ASSIGNMENT)
			{
				Crude::String KeyBuffer(Keys.At(0));
				for (unsigned int i = 1; i < Keys.Size(); i++)
				{
					KeyBuffer.Append(".").Append(Keys.At(i));
				}
				InsertValue(KeyBuffer, Buffer);
			}

			pToken = Token;
		}

		if (ComplexKeyC != 0)
			return false;

		return true;
	}

	bool Configuration::Export() {
		return false;
	}

	Crude::String Configuration::GetValue(Crude::String GetKey) {
		
		// The keys that make up the option.
		Crude::Tokenizer ValueTokenizer(GetKey, '.');
		Crude::List<Crude::String>* KeySections = ValueTokenizer.GetTokens();

		// If we have no nodes return nothing.
		if (Nodes->IsEmpty())
			return "";

		// If we are not working with a valid format quit.
		if (KeySections->IsEmpty())
			return "";

		// Save the name of the leaf node.
		Crude::String LeafNodeName = KeySections->At(KeySections->Size()-1);

		// Save the root node
		ConfigurationNode* CurrentNode = Nodes->Get(KeySections->At(0));

		// If there is no root node for the tlk return empty
		if (CurrentNode == 0)
			return "";

		// Loop through keys and explorer the children
		for (unsigned int i = 0; i < KeySections->Size(); i++)
		{
			Crude::List<ConfigurationNode*> ChildNodes = CurrentNode->GetChildren();
			for (unsigned int j = 0; j < ChildNodes.Size(); j++)
			{
				if (ChildNodes.At(j)->IsKey(KeySections->At(i)))
				{
					CurrentNode = ChildNodes.At(j);
				}
			}
		}

		if (CurrentNode->IsKey(LeafNodeName))
			return CurrentNode->GetValue();

		return "";

	}

	bool Configuration::InsertValue(Crude::String Key, Crude::String Value) {

		// The keys that make up the option.
		Crude::Tokenizer ValueTokenizer(Key, '.');
		Crude::List<Crude::String>* KeySections = ValueTokenizer.GetTokens();

		// If we are not working with a valid format quit.
		if (KeySections->IsEmpty())
			return false;

		// Start with the root node. check that there is an already existing node.
		ConfigurationNode* CurrentNode = Nodes->Get(KeySections->At(0));

		// If we dont have an existing root node then create it.
		if (CurrentNode == 0) {
			ConfigurationNode* InsertNode = 0;
			if (KeySections->Size() == 1)
				InsertNode = new ConfigurationNode(KeySections->At(0), Value);
			else
				InsertNode = new ConfigurationNode(KeySections->At(0), "<empty>");
			Nodes->Insert(KeySections->At(0), InsertNode);
			CurrentNode = Nodes->Get(KeySections->At(0));
		}

		if (KeySections->Size() > 1)
		{
			// For each section
			for (unsigned int i = 0; i < KeySections->Size(); i++)
			{

				// Are we dealing with the leaf node
				if (i+1 == KeySections->Size())
				{
					CurrentNode->AddNode(KeySections->At(i), Value);
				}

				else
				{
					CurrentNode = CreateSubNode(CurrentNode, KeySections->At(i));
				}

			}

		}

		Messages.Push(&UpdateMessage);

		return true;
	}

	ConfigurationNode* Configuration::CreateSubNode(ConfigurationNode* DestinationNode, Crude::String Key) {

		// Get the children of the node
		Crude::List<ConfigurationNode*> ChildNodes = DestinationNode->GetChildren(); bool NodeFound = false;

		// Return node
		ConfigurationNode* ReturnNode = 0;

		// Does the node already have the target key
		for (unsigned int i = 0; i < ChildNodes.Size(); i++)
			if (ChildNodes.At(i)->IsKey(Key)) {
				NodeFound = true;
				ReturnNode = ChildNodes.At(i);
			}

		if (!NodeFound)
			// Create the node
			DestinationNode->AddNode(Key, Key);
		else
			return ReturnNode;

		// Fix this later
		Crude::List<ConfigurationNode*> ChildNodes_SP = Crude::List<ConfigurationNode*>(DestinationNode->GetChildren());

		// Search for our newly installed node
		for (unsigned int i = 0; i < ChildNodes_SP.Size(); i++)
			if (ChildNodes_SP.At(i)->IsKey(Key)) {
				ReturnNode = ChildNodes_SP.At(i);
			}

		return ReturnNode;
	}

	bool Configuration::CheckCombination(int Token, int pToken) {
		if (Token == VALUE && pToken == VALUE)
			return true;
		if (Token == pToken)
			return false;
		if (pToken == ASSIGNMENT && Token != VALUE)
			return false;
		if (Token == ASSIGNMENT && pToken != VALUE)
			return false;
		return true;
	}

}