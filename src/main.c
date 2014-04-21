/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: main.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "main.h"

char *g_pAppPath;

int main(int argc, char **argv)
{
    g_pAppPath = GetApplicationPath(argv[0]);

	printf("-- irCbot v%i.%i.%i started (%s)\n", (VERSION >> 16) & 0xFF, (VERSION >> 8) & 0xFF, VERSION & 0xFF, g_pAppPath);

    if (!InitConfig(g_pAppPath))
    {
		error("-- Failed to parse configuration file\n");
		return EXIT_FAILURE;
    }

    printf("-- Successfully parsed configuration file\n");

	if(!IRC_ConnectToConfigurationNetworks())
	{
		error("-- Failed to connect to one or more networks because of threading issues\n");
		return EXIT_FAILURE;
	}

	printf("-- Successfully connected to networks specified in the configuration file\n");

    getchar();

    free(g_pAppPath);
    return EXIT_SUCCESS;
}
