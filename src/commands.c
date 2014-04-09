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
	if(iArgc && IRC_IsAuthorized(szUser))
		IRC_SendRaw(pID, "PRIVMSG %s :%s", szChannel, szArgsRaw);
}

CMD(whoami)
{
	IRC_SendRaw(pID, "PRIVMSG %s :You're %s", szChannel, szUser);
}

CMD(raw)
{
    if (IRC_IsAuthorized(szUser))
    {
        if (iArgc)
            IRC_SendRaw(pID, szArgsRaw);
        else
            IRC_SendRaw(pID, "PRIVMSG %s :Usage: .raw [Command]", szChannel);
    }
    else
        IRC_SendRaw(pID, "PRIVMSG %s :You are not authorized to use this command.", szChannel);
}

CMD(sh)
{
    if (IRC_IsAuthorized(szUser))
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
        {
            IRC_SendRaw(pID, "PRIVMSG %s :Usage: .sh [Command]", szChannel);
        }
    }
    else
    {
        IRC_SendRaw(pID, "PRIVMSG %s :You are not authorized to use this command.", szChannel);
    }
}

CMD_LIST
{
	CMDDEF(ping),
	CMDDEF(whoami),
	CMDDEF(raw),
	CMDDEF(sh),
	CMDDEF(say)
};


/*********************** stop editing here **********************/

bool IRC_ProcessCommand(struct instance_data* pID, char* user, char* channel, unsigned int partc, char **command, char* raw)
{
	unsigned int i;
	for(i = 0; i < sizeof(CMDlist)/sizeof(struct CMDstruct);++i)
	{
		if(!strcmp(CMDlist[i].str, &command[0][2]))
		{
			CMDlist[i].func(pID, user, channel, partc-4, &command[1], raw);
			return true;
		}
	}
	return false;
}
