#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/
#pragma warning(disable: 4710)
#pragma warning(disable: 4514)
#pragma warning(push, 3)
#include <time.h>
#pragma warning(pop)

namespace Crude {

	class __declspec(dllexport) Timer {
	private:
		long double m_StartTime;
		long double m_TargetTime;
	public:
		Timer(long double Tick);
		~Timer();
	public:
		void Stop();
		void Start();
		bool Finished();
	};

}