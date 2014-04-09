#ifndef IRC_H_INCLUDED
	#define IRC_H_INCLUDED

#include "stdafx.h"

int IRC_SendRaw(struct instance_data* pID, char *szRawCommand, ...);
char* IRC_GetParameterAt(const char* szLine, unsigned int iNum);
bool IRC_IsAuthorized(const char *pAddress);
void IRC_echo(struct instance_data* pID, char *pLine);

#endif // IRC_H_INCLUDED
