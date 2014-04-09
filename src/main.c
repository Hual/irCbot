/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "main.h"

char *pAppPath;

int main(int argc, char **argv) // entry point
{
    char szConfigPath[PATH_MAX]; // initialize a char array

    pAppPath = GetApplicationPath(argv[0]); // get the application path, argv[0] always stores application path
    GetNameFromPath(szConfigPath, pAppPath, "config.ini"); // append "config.ini" to the application path

    if (!IRC_SetupConfig(szConfigPath)) // load configuration from file
    {
        printf("Fatal error: Failed to load config!\n");
        goto iExitLoc;
    }

	unsigned int i;
	for(i = 0;i < ci.iServers;++i)
	{
		INSTANCE* iInstance = malloc(sizeof(INSTANCE));
		if(!IRC_AttemptConnection(&ci.pServerInfo[i], iInstance)) // connect to IP/hostname
		{
			printf("Fatal error: Failed to connect on IRC network!\n");
			goto iExitLoc;
		}
	}

    getchar();

    iExitLoc:
    return 0;
}
