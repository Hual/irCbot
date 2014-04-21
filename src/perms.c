/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: perms.c
 * @author: King_Hual <king_hell@abv.bg>
 */

#include "perms.h"

const char* g_szPermsName[] =
{
	"Ignored",
	"User",
	"Owner"
};

unsigned int GetPermissionsLevel(const struct server_info* pSI, const char *pUser)
{
	FILE *pFile;
	char pLine[512], szPath[PATH_MAX];
	GetNameFromPath(szPath, g_pAppPath, g_sCI.pData[CONFIG_BOT_PERMISSIONS]);

	if((pFile = fopen(szPath, "r")) != NULL)
	{
		char szName[512] = {0};

		while(fgets(pLine, sizeof(pLine), pFile) != NULL)
		{
			char *pValue = NULL;

			trim_right(pLine);

			if(pLine[0] == ';')
				continue;
			else if(pLine[0] == '[' && pLine[strlen(pLine)-1] == ']')
			{
				pLine[strlen(pLine)-1] = 0;
				strcpy(szName, &pLine[1]);
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

                    if(!strcmp(pSI->szName, szName) && !strcmp(pUser, pKey))
					{
						fclose(pFile);
						return atoi(pValue);
					}
				}
			}
		}
		fclose(pFile);
	}
    return PERMS_USER;
}
