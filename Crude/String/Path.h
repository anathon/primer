#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "String.h"

namespace Crude {

	/*

		Crude::Path

		A specialized string that formats a string into a valid path

	*/

	class Path {
	public:
		Path();
		Path(Crude::String PathName);
		Path(const char* PathName);
		~Path();
	private:
		Crude::String m_Data;
	public:
		Crude::String GetData();
	private:
		void Format();
	};
}