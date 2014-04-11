/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: perms.h
 * @author: King_Hual <king_hell@abv.bg>
 */

#ifndef PERMS_H_INCLUDED
	#define PERMS_H_INCLUDED

#include "stdafx.h"

#define PERMS_IGNORED 0
#define PERMS_USER 1
#define PERMS_OWNER 2

extern const char* g_szPermsName[];

unsigned int GetPermissionsLevel(const struct server_info* pSI, const char *pUser);

#endif
