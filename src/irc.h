/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.h
 * @author: King_Hual <king_hell@abv.bg>
 */

#ifndef IRC_H_INCLUDED
	#define IRC_H_INCLUDED

#include "stdafx.h"

int IRC_SendRaw(const struct instance_data* pID, const char *szRawCommand);
int IRC_SendRawEx(const struct instance_data* pID, const char *szRawCommand, ...);
int IRC_SendMessage(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendMessageEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...);
int IRC_SendNotice(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendNoticeEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...);
int IRC_SendCTCPMessage(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendAction(const struct instance_data* pID, const char* szDestination, const char* szText);

char* IRC_GetParameterAt(const char* szLine, unsigned int iNum);
void IRC_echo(struct instance_data* pID, char *pLine);

#endif // IRC_H_INCLUDED
