#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "String.h"
#include "../Containers/List.h"

/*
	Tokenizer
*/

namespace Crude {

	class Tokenizer {
	public:
		Tokenizer();
		Tokenizer( const Tokenizer &Src);
		Tokenizer( Crude::String& Values );
		Tokenizer( Crude::String& Values, const char Delim );
		Tokenizer( Crude::String& Values, const Crude::List<char> Delims );
		~Tokenizer();
	private:
		Crude::List<Crude::String>* m_pTokens;
		Crude::String m_Data;
		Crude::List<char>* m_Delims;
	public:
		void SetDelim( const Crude::List<char> Delims );
	public:
		Crude::List<Crude::String> *GetTokens();
	private:
		void _Build(Crude::String& Values);
	};

}