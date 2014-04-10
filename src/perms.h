/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: perms.h
 * @author: King_Hual <king_hell@abv.bg>
 */

#ifndef PERMS_H_INCLUDED
	#define PERMS_H_INCLUDED

#include "stdafx.h"

unsigned int GetPermissionsLevel(const struct server_info* pSI, const char *pUser);

#endif
