/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "config.h"

const static char *ppServerConfigKeys[INI_SERVER_KEYS] =
{
	"address",      /* CONFIG_SERVER_ADDRESS */
	"port",         /* CONFIG_SERVER_PORT */
	"ssl",          /* CONFIG_SERVER_SSL */
	"nickname",     /* CONFIG_SERVER_NICK */
	"username",     /* CONFIG_SERVER_USER */
	"realname",     /* CONFIG_SERVER_REAL */
	"channels",     /* CONFIG_SERVER_CHANNELS */
	"perform"       /* CONFIG_SERVER_PERFORM */
};

const static char *ppBotConfigKeys[INI_BOT_KEYS] =
{
	"cmdprefix",           /* CONFIG_BOT_PREFIX */
	"echo",                /* CONFIG_BOT_ECHO */
	"permissions",         /* CONFIG_BOT_PERMISSIONS */
	"reconnect-interval",  /* CONFIG_BOT_RECONINTERVAL */
};

struct config_info g_sCI;

static void ProcessConfigElement(char** out, const char* szKey, const char* szValue, const char** pKeyPool, const unsigned int iKeyPoolLength)
{
	signed int iIdx = GetKeyIndex(pKeyPool, szKey, iKeyPoolLength);

	if(iIdx != -1)
	{
		out[iIdx] = malloc(strlen(szValue)+1);
		strcpy(out[iIdx], szValue);
	}
}

bool InitConfig(const char *pLocation)
{
	FILE *pFile;
	char pLine[512], szFullPath[PATH_MAX];

	printf("-- Parsing configuration file...\n");

    GetNameFromPath(szFullPath, pLocation, "config.ini");

	g_sCI.iServers = 0;
	g_sCI.pServerInfo = NULL;

	if((pFile = fopen(szFullPath, "r")) != NULL)
	{
		struct server_info* csi = NULL;

		while(fgets(pLine, sizeof(pLine), pFile) != NULL)
		{
			char *pValue = NULL;

			trim_right(pLine);

			if(pLine[0] == ';')
				continue;
			else if(pLine[0] == '[' && pLine[strlen(pLine)-1] == ']')
			{
				pLine[strlen(pLine)-1] = 0;

				csi = malloc(sizeof(struct server_info)*(g_sCI.iServers+1));

				if(g_sCI.iServers)
				{
					memcpy(csi, g_sCI.pServerInfo, sizeof(struct server_info)*g_sCI.iServers);
					free(g_sCI.pServerInfo);
				}

				g_sCI.pServerInfo = csi;
				csi = g_sCI.pServerInfo+(g_sCI.iServers++);

				csi->szName = malloc(strlen(&pLine[1])+1);
				strcpy(csi->szName, &pLine[1]);
			}
			else
			{
				pValue = memchr(pLine, '=', strlen(pLine));

				if(pValue != NULL)
				{
					char* pKey;

					*pValue++ = 0;
					pKey = trim(pLine);
					pValue = trim(pValue);

					if(!g_sCI.iServers)
						ProcessConfigElement(g_sCI.pData, pKey, pValue, ppBotConfigKeys, INI_BOT_KEYS);
					else
						ProcessConfigElement(csi->pData, pKey, pValue, ppServerConfigKeys, INI_SERVER_KEYS);
				}
			}
		}

		fclose(pFile);
		return true;
	}
    return false;
}
