#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#ifdef WIN32
#include <stdint.h>
#define __int64 __int64
#else
#include <inttypes.h>
#define __int64 int64_t
#endif

#ifdef _XSTRING_ 
#ifdef _INC_STRING
#error Some gobshite has included the standard library string class
#endif
#endif

#include <assert.h>

#define cstrcpy Crude::String::_strcpy
#define cstrncpy Crude::String::_strncpy
#define cstrcpr Crude::String::_strcpr
#define cstrncpr Crude::String::_strncpr
#define cmemset Crude::String::_memset

namespace Crude {
	
	/*
		Crude::String
	
		String class, used for holding text.

		Note, Needs heavy heavy re-writing

	*/

	class __declspec(dllexport) String {
	public:
		String();
		String( const char* Value );
		String( const String &Value );
		String( const char* Value, unsigned int StartIndex );
		String( const char* Value, unsigned int StartIndex, unsigned int Count );
		~String();
	private:
		char* m_pData;
		unsigned int m_nSize;
		static const int MOD_ADLER = 65521;
	public:
		void operator=( const Crude::String &Value );
		void operator=( const char* Value );
		bool operator==( const Crude::String &Value );
		bool operator==( const char* Value );
		char operator[]( int Index );
	public:
		const char* Data();
		unsigned __int64 Hash();
		unsigned int Length();
	public:
		unsigned int Remove( char Character );
		unsigned int nRemove( char Character, unsigned int Count );
		unsigned int Replace( char Remove, char Insert );
		unsigned int nReplace( char Remove, char Insert, unsigned int Count );
		String& Append( const Crude::String &Value );
		String& Append( const char* Value );
		String& Append( const char Character );
		bool StartsWith(char Character);
		bool EndsWith(char Character);
	public:
		static unsigned int _GetSize( const char* Value );
		static void _strcpy( const char* Src, char* Dst );
		static void _strncpy( const char* Src, char* Dst, unsigned int Len );
		static bool _strcpr( const char* Src, const char* Dst );
		static bool _strncpr( const char* Src, const char* Dst, unsigned int Len );
		static void _memset(void * ptr, int value, size_t num);
	public:
		static char IntToChar(int Value);
		static String IntToString(int Value);
		static unsigned int StringToInt(String& Value);
		static void FormatLineEndings(String& Value);
		static void FormatLineEndings(char* Value, unsigned int ByteCount);
	};

	__inline char String::IntToChar(int Value) {
		if (Value > 9)
			return 0;
		return (char)(((int)'0')+Value);
	}

	__inline unsigned int String::StringToInt(String& Value) {
		unsigned int Result = 0;
		unsigned int StringLength = Value.Length();
		int Ch = 0;
		for (unsigned int i = 0;  i < StringLength; i++, Ch++) {
			if (Value[Ch] >= '0' && Value[Ch] <= '9') {
				Result = Result * 10 + Value[Ch]-48;
			}
		}
		return Result;
	}

}