/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: main.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "main.h"

char *g_pAppPath;

int main(int argc, char **argv) // entry point
{
    char szConfigPath[PATH_MAX]; // initialize a char array

    g_pAppPath = GetApplicationPath(argv[0]); // get the application path, argv[0] always stores application path
    printf("-- irCbot v%i.%i.%i started (%s) --\n", (VERSION >> 16) & 0xFF, (VERSION >> 8) & 0xFF, VERSION & 0xFF, g_pAppPath);
    GetNameFromPath(szConfigPath, g_pAppPath, "config.ini"); // append "config.ini" to the application path

    if (!IRC_SetupConfig(szConfigPath)) // load configuration from file
    {
		error("Failed to load config!\n");
		return EXIT_FAILURE;
    }

	unsigned int i;
	for(i = 0;i < g_sCI.iServers;++i)
	{
		if(!IRC_AttemptConnection(&g_sCI.pServerInfo[i], NULL)) // connect to IP/hostname
		{
			error("Failed to connect to IRC network!\n");
			return EXIT_FAILURE;
		}
	}

    getchar();
    return EXIT_SUCCESS;
}
