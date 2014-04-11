/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.c
 * @author: King_Hual <king_hell@abv.bg>
 */

#include "irc.h"

int IRC_SendRaw(const struct instance_data* pID, const char *szRawCommand) // send a raw formatted message
{
    char szBuffer[512];

	strcpy(szBuffer, szRawCommand);
    strcat(szBuffer, "\r\n");

    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

int IRC_SendRawEx(const struct instance_data* pID, const char *szRawCommand, ...) // send a raw formatted message
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

char* IRC_GetParameterAt(const char* szLine, unsigned int iNum)
{
	int i = 0;
	char* pParam;

	pParam = strchr(szLine, ' ');
	while(pParam && ++i < iNum)
		pParam = strchr(pParam+1, ' ');

	return pParam+1;
}

void IRC_echo(struct instance_data* pID, char *pLine)
{
	if(g_sCI.pData[CONFIG_BOT_ECHO][0] == '1')
		printf("%s:%i > %s\r\n", pID->cfg(CONFIG_SERVER_ADDRESS), atoi(pID->cfg(CONFIG_SERVER_PORT)), pLine);
}
