/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: irc.h
 * @author: King_Hual <king_hell@abv.bg>
 */

#ifndef IRC_H_INCLUDED
	#define IRC_H_INCLUDED

#include "stdafx.h"

int IRC_SendRaw(struct instance_data* pID, char *szRawCommand, ...);
char* IRC_GetParameterAt(const char* szLine, unsigned int iNum);
void IRC_echo(struct instance_data* pID, char *pLine);

#endif // IRC_H_INCLUDED
