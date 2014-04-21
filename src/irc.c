/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.c
 * @author: King_Hual <king_hell@abv.bg>
 */

#include "irc.h"

int IRC_SendRaw(const struct instance_data* pID, const char *szRawCommand)
{
    char szBuffer[512];

	strcpy(szBuffer, szRawCommand);
    strcat(szBuffer, "\r\n");

    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

int IRC_SendRawEx(const struct instance_data* pID, const char *szRawCommand, ...)
{
    char szBuffer[512];

    va_list iVa;
    va_start(iVa, szRawCommand);
    vsprintf(szBuffer, szRawCommand, iVa);
    va_end(iVa);
    strcat(szBuffer, "\r\n");

    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

int IRC_SendMessage(const struct instance_data* pID, const char* szDestination, const char* szText)
{
    char szBuffer[512];
	sprintf(szBuffer, "PRIVMSG %s :%s\r\n", szDestination, szText);
    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

int IRC_SendMessageEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...)
{
    char szBuffer[512];

    va_list pArgs;
    va_start(pArgs, szText);
    vsprintf(szBuffer, szText, pArgs);
    va_end(pArgs);

    return IRC_SendMessage(pID, szDestination, szBuffer);
}

int IRC_SendCTCPMessage(const struct instance_data* pID, const char* szDestination, const char* szText)
{
    char szBuffer[512];

    sprintf(szBuffer, "\x01%s\x01", szText);

    return IRC_SendMessage(pID, szDestination, szBuffer);
}

int IRC_SendAction(const struct instance_data* pID, const char* szDestination, const char* szText)
{
    char szBuffer[512];

    sprintf(szBuffer, "ACTION %s", szText);

    return IRC_SendCTCPMessage(pID, szDestination, szBuffer);
}

int IRC_SendNotice(const struct instance_data* pID, const char* szDestination, const char* szText)
{
    char szBuffer[512];
	sprintf(szBuffer, "NOTICE %s :%s\r\n", szDestination, szText);
    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

int IRC_SendNoticeEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...)
{
    char szBuffer[512];

    va_list pArgs;
    va_start(pArgs, szText);
    vsprintf(szBuffer, szText, pArgs);
    va_end(pArgs);

    return IRC_SendNotice(pID, szDestination, szBuffer);
}

int IRC_SendQuitMessage(const struct instance_data* pID, const char* szMessage)
{
    return IRC_SendRawEx(pID, "QUIT :%s", szMessage);
}

char* IRC_GetParameterAt(const char* szLine, unsigned int iNum)
{
	int i = 0;
	char* pParam;

	pParam = strchr(szLine, ' ');
	while(pParam && ++i < iNum)
		pParam = strchr(pParam+1, ' ');

	return pParam+1;
}

void IRC_EchoEx(const struct instance_data* pID, unsigned int iLevel, char* szMessage, ...)
{
    if(g_sCI.pData[CONFIG_BOT_ECHO][0] == iLevel)
	{
		char szBuffer[512];

		va_list pArgs;
		va_start(pArgs, szMessage);
		vsprintf(szBuffer, szMessage, pArgs);
		va_end(pArgs);

		printf("%s > %s\n", pID->sSI->szName, szBuffer);
	}
}

char* IRC_UserStringToStruct(struct userinfo* pUI, char* szUser)
{
	char* pUser;

	pUI->raw = szUser;
	pUser = (char*)malloc(strlen(szUser)+1);
	strcpy(pUser, szUser);
	pUI->nick = pUser;
	pUI->user = strchr(pUI->nick, '!')+1;
	if(pUI->user-1)
	{
		pUI->host = strchr(pUI->user, '@')+1;
		*(pUI->user-1) = *(pUI->host-1) = 0;
	}

	return pUser;
}

bool IRC_ConnectToConfigurationNetworks()
{
	unsigned int i;

    printf("-- Connecting to networks...\n");

	for(i = 0;i < g_sCI.iServers;++i)
		if(!IRC_AttemptConnection(&g_sCI.pServerInfo[i], NULL))
			return false;

	return true;
}
