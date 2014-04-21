/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: stdafx.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
	#define _WIN32_WINNT 0x0501
	#include <windows.h>
#else
	typedef void* HANDLE;
#endif

#define true 1
#define false 0
typedef unsigned char bool;
typedef unsigned int INSTANCE;

struct instance_data
{
#pragma pack (1)
	INSTANCE iInstance;
	struct server_info* sSI;
};

extern char *g_pAppPath;

#include "constants.h"
#include "thread.h"
#include "socket.h"
#include "irc.h"
#include "perms.h"
#include "config.h"
#include "utils.h"
#include "events.h"
#include "commands.h"
