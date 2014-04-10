/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: thread.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "stdafx.h"

#ifndef THREAD_H_INCLUDED
	#define THREAD_H_INCLUDED

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?

	#define THREAD_CALLBACK DWORD WINAPI
	#define WaitForThread(thread) WaitForSingleObject(thread, INFINITE)

	typedef HANDLE THANDLE;
#else
	#define THREAD_CALLBACK void*
	#define WaitForThread(thread) pthread_join(thread, NULL)

	typedef pthread_t THANDLE;
	typedef void* LPTHREAD_START_ROUTINE;

	#include <pthread.h>

#endif

bool StartThread(THANDLE* handle, LPTHREAD_START_ROUTINE start_routine, void* arg);

#endif // THREAD_H_INCLUDED
