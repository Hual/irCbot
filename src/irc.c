/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.c
 * @author: King_Hual <king_hell@abv.bg>
 */

#include "irc.h"

int IRC_SendRaw(struct instance_data* pID, char *szRawCommand, ...) // send a raw formatted message
{
    char szBuffer[512];

    va_list iVa;
    va_start(iVa, szRawCommand);
    vsprintf(szBuffer, szRawCommand, iVa);
    va_end(iVa);
    strcat(szBuffer, "\r\n");

    return send(pID->iInstance, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
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
		printf("%s:%i > %s\r\n", pID->sCSI->szServer, pID->sCSI->iPort, pLine);
}
