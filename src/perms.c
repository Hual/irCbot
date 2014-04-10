/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: perms.c
 * @author: King_Hual <king_hell@abv.bg>
 */

#include "perms.h"

unsigned int GetPermissionsLevel(const struct server_info* pSI, const char *pUser)
{
	FILE *pFile;
	char pLine[512], szPath[PATH_MAX];
	GetNameFromPath(szPath, g_pAppPath, g_sCI.pData[CONFIG_BOT_PERMISSIONS]);

	if((pFile = fopen(szPath, "r")) != NULL) // file was read successfully
	{
		char szServer[512] = {0};

		while(fgets(pLine, sizeof(pLine), pFile) != NULL)
		{
			char *pValue = NULL;

			trim_right(pLine);

			if(pLine[0] == ';')
				continue;
			else if(pLine[0] == '[' && pLine[strlen(pLine)-1] == ']')
			{
				pLine[strlen(pLine)-1] = 0;
				strcpy(szServer, &pLine[1]);
			}
			else
			{
				pValue = memchr(pLine, '=', strlen(pLine)); // get '=' position

				if(pValue != NULL) // '=' is found
				{
					*pValue++ = 0; // set '=' to '\0', this splits the line into 2, and pointer is set to the char after

					char* pKey = trim(pLine); // trim space from key
					pValue = trim(pValue); // trim space from value

                    if(!strcmp(pSI->szServer, szServer) && !strcmp(pUser, pKey))
					{
						fclose(pFile);
						return atoi(pValue);
					}
				}
			}
		}
		fclose(pFile);
	}
    return 0;
}
