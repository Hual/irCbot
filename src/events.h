/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include "stdafx.h"

#define ModeToString(str, str2, str3, str4, str5) strcpy(szVerb, bAdd ? str : str2); strcpy(szAction, str3); strcpy(szOther, bAdd ? str4 : str5);

void IRC_ProcessEvents(struct instance_data* pID, char *pLine);

#endif
