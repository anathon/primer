#include "String.h"

namespace Crude {

	String::String() {
		m_nSize = 0;
		m_pData = 0;
	}

	String::String( const char* Value ) {
		if (!Value) {
			m_nSize = 0;
			return;
		}
		m_nSize = _GetSize(Value);
		m_pData = new char[m_nSize+2];
		_strcpy(Value, m_pData);
	}

	String::String( const Crude::String &Value ) {
		m_pData = new char[Value.m_nSize+2];
		m_nSize = Value.m_nSize;
		_strcpy(Value.m_pData, m_pData);
	}

	String::String( const char* Value, unsigned int StartIndex ) {
		if (!Value) {
			m_nSize = 0;
			return;
		}
		m_nSize = _GetSize(Value) - StartIndex;
		m_pData = new char[m_nSize+2];
		_strcpy(Value+StartIndex, m_pData);
	}

	String::String( const char* Value, unsigned int StartIndex, unsigned int Count ) {
		if (!Value) {
			m_nSize = 0;
			return;
		}
		m_nSize = Count;
		m_pData = new char[m_nSize+2];
		_strncpy(Value+StartIndex, m_pData, Count);
	}

	void String::operator=( const Crude::String &Value ) {
		if (m_nSize > 0)
			delete[] m_pData;
		m_nSize = Value.m_nSize;
		m_pData = new char[Value.m_nSize+2];
		_strcpy(Value.m_pData, m_pData);
	}

	void String::operator=( const char* Value ) {
		if (!Value) {
			m_nSize = 0;
			return;
		}
		if (m_nSize > 0)
			delete[] m_pData;
		m_nSize = _GetSize(Value);
		m_pData = new char[m_nSize+2];
		_strcpy(Value, m_pData);
	}

	bool String::operator==( const Crude::String &Value ) {
		return cstrcpr(m_pData, Value.m_pData);
	}

	bool String::operator==( const char* Value ) {
		if (!Value)
			return false;
		return cstrcpr(m_pData, Value);
	}

	char String::operator[]( int Index ) {
		return m_pData[Index];
	}

	const char* String::Data() {
		return m_pData;
	}

	unsigned __int64 String::Hash() {
		uint64_t x, y;
		x = 1;
		y = 0;

		for (unsigned int index = 0; index < m_nSize; ++index) {
			x = (x + m_pData[index]) % MOD_ADLER;
			y = (y + x) % MOD_ADLER;
		}

		return (y << 16) | x;
	}

	unsigned int String::Length() {
		return m_nSize;
	}

	unsigned int String::Remove( char Character ) {
		if (m_nSize == 0) return 0;
		unsigned int RemovalCount = 0;

		for (unsigned int i = 0; i < m_nSize; i++) {
			m_pData[i-RemovalCount] = m_pData[i];
			if (m_pData[i] == Character) {
				RemovalCount++;
			}
		}

		if (RemovalCount > 0) {
			m_pData[m_nSize-RemovalCount] = '\0';
			m_nSize -= RemovalCount;
		}

		return RemovalCount;
	}

	unsigned int String::nRemove( char Character, unsigned int Count ) {
		if (m_nSize == 0) return 0;
		unsigned int RemovalCount = 0;

		for (unsigned int i = 0; i < m_nSize; i++) {
			m_pData[i-RemovalCount] = m_pData[i];
			if (m_pData[i] == Character) {
				if (i < Count) RemovalCount++;
			}
		}

		if (RemovalCount > 0) {
			m_pData[m_nSize-RemovalCount] = '\0';
			m_nSize -= RemovalCount;
		}

		return RemovalCount;
	}

	unsigned int String::Replace( char Remove, char Insert ) {
		unsigned int ReplaceCount = 0;
		for (unsigned int i = 0; i < m_nSize; i++) {
			if (m_pData[i] == Remove) {
				m_pData[i] = Insert;
				ReplaceCount++;
			}
		}
		return ReplaceCount;
	}

	unsigned int String::nReplace( char Remove, char Insert, unsigned int Count ) {
		unsigned int ReplaceCount = 0;
		if (Count >= m_nSize)
			return 0;
		for (unsigned int i = 0; i < Count; i++) {
			if (m_pData[i] == Remove) {
				m_pData[i] = Insert;
				ReplaceCount++;
			}
		}
		return ReplaceCount;
	}

	String& String::Append( const Crude::String &Value ) {
		unsigned int NewSize = m_nSize + Value.m_nSize;
		char* NewData = new char[NewSize+1];
		for (unsigned int i = 0; i < m_nSize; i++) {
			NewData[i] = m_pData[i];
		}
		for (unsigned int i = m_nSize, j = 0; i < NewSize; i++, j++) {
			NewData[i] = Value.m_pData[j];
		}
		NewData[NewSize] = '\0';
		delete m_pData;
		m_pData = NewData;
		m_nSize = NewSize;
		return *this;
	}

	String& String::Append( const char* Value ) {
		if (!Value) {
			return *this;
		}
		unsigned int NewSize = m_nSize + _GetSize(Value);
		char* NewData = new char[NewSize+1];
		for (unsigned int i = 0; i < m_nSize; i++) {
			NewData[i] = m_pData[i];
		}
		for (unsigned int i = m_nSize, j = 0; i < NewSize; i++, j++) {
			NewData[i] = Value[j];
		}
		NewData[NewSize] = '\0';
		delete m_pData;
		m_pData = NewData;
		m_nSize = NewSize;
		return *this;
	}

	String& String::Append( const char Character ) {
		unsigned int NewSize = m_nSize + 1;
		char* NewData = new char[NewSize+1];
		for (unsigned int i = 0; i < m_nSize; i++) {
			NewData[i] = m_pData[i];
		}
		NewData[NewSize-1] = Character;
		NewData[NewSize] = '\0';
		delete m_pData;
		m_pData = NewData;
		m_nSize = NewSize;
		return *this;
	}

	bool String::StartsWith(char Character) {
		if (m_pData[0] == Character)
			return true;
		return false;
	}

	bool String::EndsWith(char Character) {
		if (m_pData[m_nSize-1] == Character)
			return true;
		return false;
	}

	unsigned int String::_GetSize(const char* Value) {
		if (!Value)
			return 0;
		unsigned int cIndex = 0;
		while(Value[cIndex] != '\0')
			cIndex++;
		return cIndex;
	}

	void String::_strcpy(const char* Src, char* Dst) {
		if (!Src)
			return;
		if (!Dst)
			return;
		unsigned int cIndex = 0;
		while(Src[cIndex] != '\0') {
			Dst[cIndex] = Src[cIndex];
			cIndex++;
		}
		Dst[cIndex] = '\0';
	}

	void String::_strncpy(const char* Src, char* Dst, unsigned int Len) {
		if (!Src)
			return;
		if (!Dst)
			return;
		for (unsigned int i = 0; i < Len; i++) {
			Dst[i] = Src[i];
		}
		Dst[Len] = '\0';
	}

	bool String::_strcpr(const char* Src, const char* Dst) {
		if (!Src)
			return false;
		if (!Dst)
			return false;
		unsigned int cIndex = 0;
		while(Src[cIndex] != '\0') {
			int Comparison = int(Src[cIndex]) - int(Dst[cIndex]);
			if (Comparison)
				return false;
			cIndex++;
		}
		if (Dst[cIndex] != '\0')
			return false;
		return true;
	}

	bool String::_strncpr(const char* Src, const char* Dst, unsigned int Len) {
		if (!Src)
			return false;
		if (!Dst)
			return false;
		unsigned int cIndex = 0;
		for (cIndex = 0; cIndex < Len; cIndex++) {
			if (Src[cIndex] == '\0')
				break;
			int Comparison = int(Src[cIndex]) - int(Dst[cIndex]);
			if (Comparison)
				return false;
			cIndex++;
		}
		if (Dst[cIndex] != '\0')
			return false;
		return true;
	}

	void String::_memset(void * ptr, int value, size_t num) {
		if (!ptr)
			return;
		if (num) {
		for(unsigned int i = 0; i < num; i++) {
			((int*)ptr)[i] = value;
		}}
	}

	// Credit to - Kernighan and Ritchie's The C Programming Language
	String String::IntToString(int Value) {
		int i, sign;
		char buffer[20];
		if ((sign = Value) < 0)
			Value = -Value;
		i = 0;
		do {
			buffer[i++] = Value % 10 + '0';
		} while ((Value /= 10) > 0);

		if (sign < 0)
			buffer[i++] = '-';
		buffer[i] = '\0';

		unsigned int k, l;
 
		for (k = 0, l = _GetSize(buffer)-1; k<l; k++, l--) {
			char c = buffer[k];
			buffer[k] = buffer[l];
			buffer[l] = c;
		}

		return Crude::String(buffer);
	}

	void String::FormatLineEndings(String& Value) {
		char* InternalData = Value.m_pData;
		for(unsigned int i = 0; i < Value.Length(); i++)
		{
			if (InternalData[i] == '\r')
				InternalData[i] = '\n';
		}
	}

	void String::FormatLineEndings(char* Value, unsigned int ByteCount) {
		for(unsigned int i = 0; i < ByteCount; i++)
		{
			if (Value[i] == '\r')
				Value[i] = '\n';
		}
	}

	String::~String() {
		if (m_nSize > 0)
			delete[] m_pData;
	}
}