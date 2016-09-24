/*****************************************************************************
*  Copyright{ 2016 } {Abhijit Bhattacharjee(itabhijitb@gmail.com)}           *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
******************************************************************************/
#ifndef __PROFILER_TIMER_H__
#define __PROFILER_TIMER_H__
/*****************************************************************************/
/*                        WINDOWS/POSIX Libraries                            */
/*****************************************************************************/
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

/*****************************************************************************/
/*                           PROJECT Libraries                               */
/*****************************************************************************/
#include "OOTestException.h"

namespace OOTestNS {
#ifdef WIN32
	class Timer
	{
		double PCFreq;
		__int64 CounterStart;
	public:
		Timer() : PCFreq(0.0), CounterStart(0)
		{

			LARGE_INTEGER li;
			if (!QueryPerformanceFrequency(&li))
				ProfilerException("QueryPerformanceFrequency failed");

			PCFreq = double(li.QuadPart) / 1000.0;

			QueryPerformanceCounter(&li);
			CounterStart = li.QuadPart;

		};
		double End()
		{
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			return double(li.QuadPart - CounterStart) / PCFreq;
		};
	};
#else
	class Timer
	{
		double m_start, m_end;
		double getCPUTime()
		{
#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
				/* AIX, BSD, Cygwin, HP-UX, Linux, OSX, and Solaris --------- */

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
				/* Prefer high-res POSIX timers, when available. */
			{
				clockid_t id;
				struct timespec ts;
#if _POSIX_CPUTIME > 0
				/* Clock ids vary by OS.  Query the id, if possible. */
				if ( clock_getcpuclockid( 0, &id ) == -1 )
#endif
#if defined(CLOCK_PROCESS_CPUTIME_ID)
					/* Use known clock id for AIX, Linux, or Solaris. */
					id = CLOCK_PROCESS_CPUTIME_ID;
#elif defined(CLOCK_VIRTUAL)
					/* Use known clock id for BSD or HP-UX. */
					id = CLOCK_VIRTUAL;
#else
					id = (clockid_t)-1;
#endif
				if (id != (clockid_t)-1 && clock_gettime(id, &ts) != -1)
					return (double)ts.tv_sec +
					(double)ts.tv_nsec / 1000000000.0;
}
#endif

#if defined(RUSAGE_SELF)
{
	struct rusage rusage;
	if (getrusage(RUSAGE_SELF, &rusage) != -1)
		return (double)rusage.ru_utime.tv_sec +
		(double)rusage.ru_utime.tv_usec / 1000000.0;
}
#endif

#if defined(CLOCKS_PER_SEC)
	{
		clock_t cl = clock();
		if (cl != (clock_t)-1)
			return (double)cl / (double)CLOCKS_PER_SEC;
	}
#endif

#endif

			return -1;		/* Failed. */
}
	public:
		Timer() : m_end(0), m_start(getCPUTime()) {}
		double End()
		{
			m_end = getCPUTime();
			return m_end - m_start;
		};
	};
#endif //WIN32
	
}
#endif //__PROFILER_TIMER_H__
