/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: utils.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "stdafx.h"

struct system_print_params
{
#pragma pack (1)
	struct instance_data* pID;
	char* pChannel;
	char* pArgs;
};

unsigned int explode(char ***arr_ptr, char *str, char delimiter);
char* GetApplicationPath(char* szMargv0);
void GetNameFromPath(char* lpOut, const char* szPath, const char* szName);
signed int GetKeyIndex(const char** ppKeys, const char* szKey, const unsigned int len);
char* trim_left(char *szString);
void trim_right(char *szString);
char* trim(char* szString);
char* replace_first(char* szString, const char cChr, const char cReplacement);
void error(const char* szString, ...);

THREAD_CALLBACK system_print(void* lpParam);

#endif
