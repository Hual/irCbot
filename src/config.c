/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "config.h"

const static char *ppServerConfigKeys[INI_SERVER_KEYS] = // a private constant array that stores keys
{
	"ssl",          // CONFIG_SERVER_SSL
	"nickname",     // CONFIG_SERVER_NICK
	"username",     // CONFIG_SERVER_USER
	"realname",     // CONFIG_SERVER_REAL
	"channels",     // CONFIG_SERVER_CHANNELS
	"perform"       // CONFIG_SERVER_PERFORM
};

const static char *ppBotConfigKeys[INI_BOT_KEYS] =
{
	"cmdprefix",    // CONFIG_BOT_PREFIX
	"echo",         // CONFIG_BOT_ECHO
};

struct config_info ci;

static void IRC_ProcessConfigElement(char** out, const char* szKey, const char* szValue, const char** pKeyPool, const unsigned int iKeyPoolLength)
{
	signed int iIdx = GetKeyIndex(pKeyPool, szKey, iKeyPoolLength); // get the index of the key (to be stored in the appropriate index in ppConfig)

	if(iIdx != -1) // if key is valid
	{
		out[iIdx] = malloc(strlen(szValue)+1); // store value in global configuration values array
		strcpy(out[iIdx], szValue);
	}
}

bool IRC_SetupConfig(const char *pLocation)
{
	FILE *pFile;
	char pLine[512];

	ci.iServers = 0;
	ci.pServerInfo = NULL;

	if((pFile = fopen(pLocation, "r")) != NULL) // file was read successfully
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
				char* pPort = strchr(pLine, ':');
				*pPort++ = 0;

				csi = malloc(sizeof(struct server_info)*(ci.iServers+1));

				if(ci.iServers)
				{
					memcpy(csi, ci.pServerInfo, sizeof(struct server_info)*ci.iServers);
					free(ci.pServerInfo);
				}

				ci.pServerInfo = csi;
				csi = ci.pServerInfo+(ci.iServers++);

				csi->szServer = malloc(strlen(&pLine[1])+1);
				strcpy(csi->szServer, &pLine[1]);
				csi->iPort = atoi(pPort);
			}
			else
			{
				pValue = memchr(pLine, '=', strlen(pLine)); // get '=' position

				if(pValue != NULL) // '=' is found
				{
					*pValue++ = 0; // set '=' to '\0', this splits the line into 2, and pointer is set to the char after

					char* pKey = trim(pLine); // trim space from key
					pValue = trim(pValue); // trim space from value

					if(!ci.iServers)
						IRC_ProcessConfigElement(ci.pData, pKey, pValue, ppBotConfigKeys, INI_BOT_KEYS);
					else
						IRC_ProcessConfigElement(csi->pData, pKey, pValue, ppServerConfigKeys, INI_SERVER_KEYS);
				}
			}
		}

		fclose(pFile);
		return true; // success
	}
    return false; // error
}
