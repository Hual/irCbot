/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.c
 * @authors: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "events.h"

static void IRC_OnChannelJoin(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel)
{
	IRC_EchoEx(pID, '2', "[%s] %s (%s@%s) has joined", szChannel, pUI->nick, pUI->user, pUI->host);

	/* TODO: do stuff */
}

static void IRC_OnNicknameChange(const struct instance_data* pID, const struct userinfo* pUI, const char* pNewNick)
{
	IRC_EchoEx(pID, '2', "[global] %s is now known as %s", pUI->nick, pNewNick);

    /* TODO: do stuff */
}

static void IRC_OnChannelPart(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szMessage)
{
	IRC_EchoEx(pID, '2', "[%s] %s has left (%s)", szChannel, pUI->nick, szMessage);

    /* TODO: do stuff */
}

static void IRC_OnChannelAction(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szMessage)
{
	IRC_EchoEx(pID, '2', "[%s] * %s %s", szChannel, pUI->nick, szMessage);

	/* TODO: do stuff */
}

static void IRC_OnPrivateAction(const struct instance_data* pID, const struct userinfo* pUI, const char* szMessage)
{
	IRC_EchoEx(pID, '2', "[query] * %s %s", pUI->nick, szMessage);

	/* TODO: do stuff */
}

static void IRC_OnChannelCTCPMessage(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szMessage)
{
	if(!strncmp("ACTION ", szMessage, 7))
		IRC_OnChannelAction(pID, pUI, szChannel, &szMessage[7]);
	else
	{
		IRC_EchoEx(pID, '2', "[%s] %s->CTCP (%s)", szChannel, pUI->nick, szMessage);

		/* TODO: do stuff */
	}
}

static void IRC_OnPrivateCTCPMessage(const struct instance_data* pID, const struct userinfo* pUI, const char* szMessage)
{
	if(!strncmp("ACTION ", szMessage, 7))
		IRC_OnPrivateAction(pID, pUI, &szMessage[7]);
	else
	{
		IRC_EchoEx(pID, '2', "[query] %s->CTCP (%s)", pUI->nick, szMessage);

		/* TODO: do stuff */
	}
}

static void IRC_OnChannelMessage(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szMessage)
{
	IRC_EchoEx(pID, '2', "[%s] <%s> %s", szChannel, pUI->nick, szMessage);

	/* TODO: do stuff */
}

static void IRC_OnPrivateMessage(const struct instance_data* pID, const struct userinfo* pUI, const char* szMessage)
{
	IRC_EchoEx(pID, '2', "[query] <%s> %s", pUI->nick, szMessage);

	/* TODO: do stuff */
}

static void IRC_OnKick(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szKickedNick, const char* szReason)
{
	IRC_EchoEx(pID, '2', "[%s] %s has kicked %s (%s)",  szChannel, pUI->nick, szKickedNick, szReason);

    /* TODO: do stuff */
}

static void IRC_OnQuit(const struct instance_data* pID, const struct userinfo* pUI, const char* szReason)
{
	IRC_EchoEx(pID, '2', "[global] %s has quit (%s)", pUI->nick, szReason);

	/* TODO: do stuff */
}

static void IRC_OnNicknameConflict(const struct instance_data* pID)
{
    IRC_SendRawEx(pID, "NICK %s`%d", pID->cfg(CONFIG_SERVER_NICK), rand() % 0xFFFF);

    /* TODO: do stuff */
}

static void IRC_OnBotConnect(const struct instance_data* pID)
{
    char **pPerform;
    int iSize, iIdx;

	IRC_EchoEx(pID, '2', "* Registered with network");

    IRC_SendRawEx(pID, "JOIN %s", pID->cfg(CONFIG_SERVER_CHANNELS));

    iSize = explode(&pPerform, pID->cfg(CONFIG_SERVER_PERFORM), '~');
    for (iIdx = 0; iIdx != iSize; ++ iIdx)
        IRC_SendRawEx(pID, pPerform[iIdx]);

	free(pPerform);

	/* TODO: do stuff */
}

static void IRC_OnChannelBan(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szHostmask)
{
	/* TODO: do stuff */
}

static void IRC_OnChannelUnban(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szHostmask)
{
	/* TODO: do stuff */
}

static void IRC_OnChannelVoice(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelDeVoice(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
	/* TODO: do stuff */
}

static void IRC_OnChannelHalfOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelDeHalfOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelDeOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelSuperOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelDeSuperOp(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelOwner(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelDeOwner(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szTargetNick)
{
    /* TODO: do stuff */
}

static void IRC_OnChannelMode(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const bool bAdd, const char cMode, const char* pParam)
{
	if(g_sCI.pData[CONFIG_BOT_ECHO][0] == '2')
	{
		char szAction[8], szVerb[8], szOther[5];

		switch(cMode)
		{
			case 'b':
				ModeToString("sets", "removes", "ban", "on", "on");
				break;
			case 'v':
				ModeToString("gives", "takes", "voice", "to", "from");
				break;
			case 'h':
				ModeToString("gives", "takes", "half-op", "to", "from");
				break;
			case 'o':
				ModeToString("gives", "takes", "op", "to", "from");
				break;
			case 'a':
				ModeToString("gives", "takes", "admin", "to", "from");
				break;
			case 'q':
				ModeToString("gives", "takes", "owner", "to", "from");
				break;
			case 'k':
				ModeToString("sets", "unsets", "keyword", "to", "from");
				break;
			default:
				strcpy(szVerb, "sets");
				strcpy(szAction, "mode");
				szOther[0] = bAdd ? '+' : '-';
				szOther[1] = cMode;
				szOther[2] = 0;
		}

		IRC_EchoEx(pID, '2', "[%s] %s %s %s %s %s", szChannel, pUI->nick, szVerb, szAction, szOther, pParam);
	}

	/* TODO: do stuff */
}

static void IRC_OnChannelModeRaw(const struct instance_data* pID, const struct userinfo* pUI, const char* szChannel, const char* szModes, const unsigned int iArgc, char** ppArgv, const char* szRaw)
{
    bool bAdd = true;
    unsigned int i, iCurrParam;

	/* code is a mess, will have to rewrite it */
    for(i = iCurrParam = 0;i < strlen(szModes);++i)
    {
        switch(szModes[i])
        {
		case '+':
            bAdd = true;
            break;
		case '-':
			bAdd = false;
			break;
		case 'b':
			if(bAdd)
				IRC_OnChannelBan(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelUnban(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
		case 'v':
			if(bAdd)
				IRC_OnChannelVoice(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelDeVoice(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
		case 'h':
			if(bAdd)
				IRC_OnChannelHalfOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelDeHalfOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
		case 'o':
			if(bAdd)
				IRC_OnChannelOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelDeOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
		case 'a':
			if(bAdd)
				IRC_OnChannelSuperOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelDeSuperOp(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
		case 'q':
			if(bAdd)
				IRC_OnChannelOwner(pID, pUI, szChannel, ppArgv[iCurrParam]);
			else
				IRC_OnChannelDeOwner(pID, pUI, szChannel, ppArgv[iCurrParam]);
			break;
        }

        switch(szModes[i])
        {
		case '+':
		case '-':
			break;
		case 'b':
		case 'v':
		case 'h':
		case 'o':
		case 'a':
		case 'q':
		case 'k':
			IRC_OnChannelMode(pID, pUI, szChannel, bAdd, szModes[i], ppArgv[iCurrParam++]);
			break;
		default:
			IRC_OnChannelMode(pID, pUI, szChannel, bAdd, szModes[i], "");
        }
    }

	/* TODO: do stuff */
}

static void IRC_OnServerPing(const struct instance_data* pID, const char* szMessage)
{
	IRC_SendRawEx(pID, "PONG %s", szMessage);

	/* TODO: do stuff */
}

void IRC_ProcessEvents(struct instance_data* pID, char* pLine)
{
    char **pParts;
    unsigned int iSize;

    trim_right(pLine);
    iSize = explode(&pParts, pLine, ' ');

	IRC_EchoEx(pID, '1', pLine);
	if(!strcmp(pParts[0], "ERROR"))
	{
		IRC_EchoEx(pID, '2', "* Critical error occurred: %s", IRC_GetParameterAt(pLine, 1)+1);
		IRC_SendQuitMessage(pID, "Closed connection");
		CloseConnection(pID);
	}
	else if(!strcmp(pParts[0], "PING"))
	{
		IRC_OnServerPing(pID, pParts[1]);
	}
    else if(pParts[0] && pParts[1])
    {
    	struct userinfo sUI;
		char* pToFree = IRC_UserStringToStruct(&sUI, &pParts[0][1]);

		if (!strcmp(pParts[1], "JOIN"))
        {
			IRC_OnChannelJoin(pID, &sUI, &pParts[2][1]);
        }
        else if (!strcmp(pParts[1], "PART"))
        {
        	char* pMessage = IRC_GetParameterAt(pLine, 3);
			IRC_OnChannelPart(pID, &sUI, pParts[2], (unsigned int)pMessage > 1 ? &pMessage[1] : "");
        }
        else if (!strcmp(pParts[1], "KICK"))
        {
        	char* pMessage = IRC_GetParameterAt(pLine, 4);
			IRC_OnKick(pID, &sUI, pParts[2], pParts[3], (unsigned int)pMessage > 1 ? &pMessage[1] : "");
        }
        else if (!strcmp(pParts[1], "QUIT"))
        {
			char* pMessage = IRC_GetParameterAt(pLine, 3);
			IRC_OnQuit(pID, &sUI, (unsigned int)pMessage > 1 ? &pMessage[1] : "");
        }
        else if (!strcmp(pParts[1], "MODE"))
        {
            if(pParts[2][0] == '#')
				IRC_OnChannelModeRaw(pID, &sUI, pParts[2], pParts[3], iSize-4, &pParts[4], IRC_GetParameterAt(pLine, 3));
        }
        else if (!strcmp(pParts[1], "NICK"))
        {
			IRC_OnNicknameChange(pID, &sUI, &pParts[2][1]);
        }
        else if (!strcmp(pParts[1], "TOPIC"))
        {

        }
        else if (!strcmp(pParts[1], "NOTICE"))
        {

        }
        else if (!strcmp(pParts[1], "PRIVMSG"))
        {
        	char* pMessage = IRC_GetParameterAt(pLine, 3)+1;

            switch (pParts[2][0])
            {
                case '#':
                case '+':
                case '%':
                case '@':
                {
                    if(!strncmp(g_sCI.pData[CONFIG_BOT_PREFIX], &pParts[3][1], strlen(g_sCI.pData[CONFIG_BOT_PREFIX])))
                        IRC_ProcessCommand(pID, &sUI, pParts[2], iSize, &pParts[3], IRC_GetParameterAt(pLine, 4));
					else if(pParts[3][1] != 1)
						IRC_OnChannelMessage(pID, &sUI, pParts[2], pMessage);
					else
					{
						*(pMessage+strlen(pMessage)-1) = 0;
						IRC_OnChannelCTCPMessage(pID, &sUI, pParts[2], &pMessage[1]);
					}
                    break;
                }
                default:
                {
					if(pParts[3][1] != 1)
						IRC_OnPrivateMessage(pID, &sUI, pMessage);
					else
					{
						*(pMessage+strlen(pMessage)-1) = 0;
						IRC_OnPrivateCTCPMessage(pID, &sUI, &pMessage[1]);
					}
                }
            }
        }
        else
        {
            if (!strcmp(pParts[1], "001"))
            {
                IRC_OnBotConnect(pID);
            }
            else if (!strcmp(pParts[1], "433"))
            {
                IRC_OnNicknameConflict(pID);
            }
        }
        free(pToFree);
    }
    free(pParts);
}
