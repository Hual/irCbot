/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef CONFIG_H_INCLUDED
	#define CONFIG_H_INCLUDED

#include "stdafx.h"

/* configuration definitions */

#define CONFIG_SERVER_ADDRESS 0
#define CONFIG_SERVER_PORT 1
#define CONFIG_SERVER_SSL 2
#define CONFIG_SERVER_NICK 3
#define CONFIG_SERVER_USER 4
#define CONFIG_SERVER_REAL 5
#define CONFIG_SERVER_CHANNELS 6
#define CONFIG_SERVER_PERFORM 7

#define CONFIG_BOT_PREFIX 0
#define CONFIG_BOT_ECHO 1
#define CONFIG_BOT_PERMISSIONS 2

#define INI_SERVER_KEYS 8
#define INI_BOT_KEYS 3

#define cfg(a) sCSI->pData[a]

struct server_info
{
	char* szName;
	char* pData[INI_SERVER_KEYS];
};

struct config_info
{
	char* pData[INI_BOT_KEYS];
	unsigned int iServers;
	struct server_info* pServerInfo;
};

extern struct config_info g_sCI;

bool IRC_SetupConfig(const char *szLocation); // IRC_SetupConfig method, used to load the configuration from the file

#endif // CONFIG_H_INCLUDED
