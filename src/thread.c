/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: thread.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "thread.h"

bool StartThread(THANDLE* handle, LPTHREAD_START_ROUTINE start_routine, void* arg)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?

	THANDLE thHandle = CreateThread(NULL, 0, start_routine, arg, 0, NULL); // call windows' CreateThread
	*handle = thHandle; // set 'handle' to point to thHandle

	return thHandle != 0; // return 1 on success, 0 on error
	#else

	return !pthread_create(handle, NULL, start_routine, arg); // call posix' pthread_create, return its return value

	#endif
}
