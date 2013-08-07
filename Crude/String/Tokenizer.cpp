#include "Tokenizer.h"

namespace Crude {

	Tokenizer::Tokenizer() {
		m_pTokens = new List<Crude::String>(0);
		m_Delims = 0;
	}

	Tokenizer::Tokenizer( const Tokenizer &Src ) : m_pTokens(Src.m_pTokens), m_Data(Src.m_Data), m_Delims(Src.m_Delims) {
	}

	Tokenizer::Tokenizer( Crude::String& Values ) : m_Data(Values) {
		m_pTokens = new List<Crude::String>(Values.Length()/2);
		m_Delims = 0;
	}

	Tokenizer::Tokenizer( Crude::String& Values, const char Delim ) : m_Data(Values) {
		m_pTokens = new List<Crude::String>(Values.Length()/2);
		m_Delims = new Crude::List<char>(1);
		m_Delims->Insert(Delim);
	}

	Tokenizer::Tokenizer( Crude::String& Values, const Crude::List<char> Delims ) : m_Data(Values) {
		m_pTokens = new List<Crude::String>(Values.Length()/2);
		this->m_Delims = new Crude::List<char>(Delims);
	}

	void Tokenizer::SetDelim( const Crude::List<char> Delims ) {
		this->m_Delims = new Crude::List<char>(Delims);
	}

	List<Crude::String>* Tokenizer::GetTokens() {
		_Build(m_Data);
		return m_pTokens;
	}

	void Tokenizer::_Build(Crude::String& Values) {
		if (Values.Length() == 0) {
			return;
		}

		m_pTokens->Clear();

		int Ch = 0;
		for (unsigned int i = 0, j = 0; i < Values.Length(); i++, Ch++) {
			for(unsigned int k = 0; k < m_Delims->Size(); k++) {
				if (Values[Ch] == (*m_Delims)[k]) {
					if (i-j != 0) {
						m_pTokens->Insert(Crude::String(Values.Data(), j, i-j));
					}
					j = i+1;
				}
			}

			if (i+1 >= Values.Length() && j+1 <= Values.Length()) {
				m_pTokens->Insert(Crude::String(Values.Data(), j, Values.Length()-j));
			}
		}
	}

	Tokenizer::~Tokenizer() {
		if (m_Delims)
			delete m_Delims;
		if (m_pTokens)
			delete m_pTokens;
	}
}