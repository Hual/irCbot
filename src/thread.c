/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: thread.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "thread.h"

bool StartThread(THANDLE* handle, LPTHREAD_START_ROUTINE start_routine, void* arg)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))

	THANDLE thHandle = CreateThread(NULL, 0, start_routine, arg, 0, NULL);
	*handle = thHandle;

	return thHandle != 0;
	#else

	return !pthread_create(handle, NULL, start_routine, arg);

	#endif
}

void ThreadSleep(unsigned int iTime)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
		Sleep(iTime);
	#else
		usleep(iTime*1000);
	#endif
}
