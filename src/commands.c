/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "commands.h"

/********************** start editing here **********************/


/* (struct instance_data* pID, struct userinfo* pUI, char* szChannel, unsigned int iArgc, char** ppArgs, char* szArgsRaw) */

CMD(ping)
{
	IRC_SendMessage(pID, szChannel, "Pong!");
}

CMD(do)
{
	if(iArgc)
		IRC_SendAction(pID, szChannel, szArgsRaw);
	else
		IRC_SendMessage(pID, szChannel, "Usage: .do [command]");
}

CMD(say)
{
	if(iArgc)
		IRC_SendMessage(pID, szChannel, szArgsRaw);
}

CMD(whoami)
{
	IRC_SendMessageEx(pID, szChannel, "You're %s", pUI->raw);
}

CMD(raw)
{
	if (iArgc)
		IRC_SendRawEx(pID, szArgsRaw);
	else
		IRC_SendMessage(pID, szChannel, "Usage: .raw [command]");
}

CMD(sh)
{
	if (iArgc)
	{
		char* _szChannel, * szArgs;
		struct system_print_params* sspp;
		THANDLE handle;
		_szChannel = malloc(64);
		szArgs = malloc(512);
		strcpy(_szChannel, szChannel);
		strcpy(szArgs, szArgsRaw);

		sspp = (struct system_print_params*)malloc(sizeof(struct system_print_params));
		sspp->pID = pID;
		sspp->pChannel = _szChannel;
		sspp->pArgs = szArgs;

		StartThread(&handle, system_print, (void*)sspp);
	}
	else
		IRC_SendMessage(pID, szChannel, "Usage: .sh [command]");
}

CMD(mylvl)
{
	unsigned int iLevel = GetPermissionsLevel(pID->sSI, pUI->raw);
	IRC_SendMessageEx(pID, szChannel, "Your permissions level: %i (%s)", iLevel, g_szPermsName[iLevel]);
}

CMD_LIST
{
	CMDDEF(ping),
	CMDDEF(whoami),
	CMDDEF(mylvl),
	CMDDEF_(do, PERMS_OWNER),
	CMDDEF_(raw, PERMS_OWNER),
	CMDDEF_(sh, PERMS_OWNER),
	CMDDEF_(say, PERMS_OWNER)
};


/*********************** stop editing here **********************/

bool IRC_ProcessCommand CMDPARAMS
{
	unsigned int i;
	for(i = 0; i < sizeof(CMDlist)/sizeof(struct CMDstruct);++i)
	{
		if(!strcmp(CMDlist[i].szName, ppArgs[0]+strlen(g_sCI.pData[CONFIG_BOT_PREFIX])+1) && GetPermissionsLevel(pID->sSI, pUI->raw) >= CMDlist[i].iLevel)
		{
			CMDlist[i].pFunc(pID, pUI, szChannel, iArgc-4, &ppArgs[1], szArgsRaw);
			return true;
		}
	}
	return false;
}
