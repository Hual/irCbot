/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "commands.h"

/********************** start editing here **********************/

// (struct instance_data* pID, char* szUser, char* szChannel, unsigned int iArgc, char** ppArgs, char* szArgsRaw)

CMD(ping)
{
	IRC_SendRaw(pID, "PRIVMSG %s :Pong!", szChannel);
}

CMD(say)
{
	if(iArgc)
		IRC_SendRaw(pID, "PRIVMSG %s :%s", szChannel, szArgsRaw);
}

CMD(whoami)
{
	IRC_SendRaw(pID, "PRIVMSG %s :You're %s", szChannel, szUser);
}

CMD(raw)
{
	if (iArgc)
		IRC_SendRaw(pID, szArgsRaw);
	else
		IRC_SendRaw(pID, "PRIVMSG %s :Usage: .raw [command]", szChannel);
}

CMD(sh)
{
	if (iArgc)
	{
		char* _szChannel, * szArgs;
		_szChannel = malloc(64);
		szArgs = malloc(512);
		strcpy(_szChannel, szChannel);
		strcpy(szArgs, szArgsRaw);

		struct system_print_params* sspp = (struct system_print_params*)malloc(sizeof(struct system_print_params));
		sspp->pID = pID;
		sspp->pChannel = _szChannel;
		sspp->pArgs = szArgs;

		THANDLE handle;
		StartThread(&handle, system_print, (void*)sspp);

	}
	else
		IRC_SendRaw(pID, "PRIVMSG %s :Usage: .sh [command]", szChannel);
}

CMD(mylvl)
{
	IRC_SendRaw(pID, "PRIVMSG %s :Your permissions level: %i", szChannel, GetPermissionsLevel(pID->sCSI, szUser));
}

CMD_LIST
{
	CMDDEF(ping, 0),
	CMDDEF(whoami, 0),
	CMDDEF(raw, 2),
	CMDDEF(sh, 2),
	CMDDEF(say, 2),
	CMDDEF(mylvl, 0)
};


/*********************** stop editing here **********************/

bool IRC_ProcessCommand CMDPARAMS
{
	unsigned int i;
	for(i = 0; i < sizeof(CMDlist)/sizeof(struct CMDstruct);++i)
	{
		if(!strcmp(CMDlist[i].szName, &ppArgs[0][2]) && GetPermissionsLevel(pID->sCSI, szUser) >= CMDlist[i].iLevel)
		{
			CMDlist[i].fFunc(pID, szUser, szChannel, iArgc-4, &ppArgs[1], szArgsRaw);
			return true;
		}
	}
	return false;
}
