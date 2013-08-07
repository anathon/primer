#include "Time.h"

#pragma warning(disable: 4710)
#pragma warning(disable: 4514)
#pragma warning(push, 3)

#include <ctime>
#include <stdio.h>
#include <stdarg.h>

#pragma warning(pop)


namespace Crude {

	Crude::String Time::GetDateTime() {
		struct tm newtime;
		char am_pm[] = "AM";
		__time64_t long_time;
		char timebuf[26];

		_time64( &long_time );
		_localtime64_s( &newtime, &long_time );
		if( newtime.tm_hour > 12 )
				cstrncpy( "PM", am_pm, 2 );
		if( newtime.tm_hour > 12 )
				newtime.tm_hour -= 12;
		if( newtime.tm_hour == 0 )
				newtime.tm_hour = 12; 
		asctime_s(timebuf, 26, &newtime);
		char* return_buffer = new char[256];
		sprintf_s(return_buffer, 256, "%.19s %s: ", timebuf, am_pm);
		return return_buffer;
	}

}