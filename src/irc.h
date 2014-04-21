/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.h
 * @author: King_Hual <king_hell@abv.bg>
 */

#ifndef IRC_H_INCLUDED
	#define IRC_H_INCLUDED

struct userinfo
{
    char *raw;
    char *nick;
    char *user;
    char *host;
};

#include "stdafx.h"

int IRC_SendRaw(const struct instance_data* pID, const char *szRawCommand);
int IRC_SendRawEx(const struct instance_data* pID, const char *szRawCommand, ...);
int IRC_SendMessage(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendMessageEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...);
int IRC_SendNotice(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendNoticeEx(const struct instance_data* pID, const char* szDestination, const char* szText, ...);
int IRC_SendCTCPMessage(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendAction(const struct instance_data* pID, const char* szDestination, const char* szText);
int IRC_SendQuitMessage(const struct instance_data* pID, const char* szMessage);

char* IRC_UserStringToStruct(struct userinfo* pUI, char* szUser);
char* IRC_GetParameterAt(const char* szLine, unsigned int iNum);
void IRC_EchoEx(const struct instance_data* pID, unsigned int iLevel, char* szMessage, ...);
bool IRC_ConnectToConfigurationNetworks();

#endif
