/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "stdafx.h"

#define CMDDEF(cmd) { (#cmd), (CMD_##cmd) }
#define CMD_LIST static struct CMDstruct CMDlist[] =
#define CMDPARAMS (struct instance_data* pID, char* szUser, char* szChannel, unsigned int iArgc, char** ppArgs, char* szArgsRaw)
#define CMD(cmd) static void CMD_##cmd CMDPARAMS

struct CMDstruct
{
	char* str;
	void (*func) CMDPARAMS;
};
char *pAppPath;
bool IRC_ProcessCommand CMDPARAMS;
bool IRC_IsAuthorized(const char *pAddress);
#endif // COMMANDS_H_INCLUDED
