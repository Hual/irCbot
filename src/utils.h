/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <ctype.h>
#include "stdafx.h"
#include "thread.h"

struct system_print_params
{
	struct instance_data* pID;
	char* pChannel;
	char* pArgs;
};

unsigned int explode(char ***arr_ptr, char *str, char delimiter);
char* GetApplicationPath(char* szMargv0); // gets the application path
void GetNameFromPath(char* lpOut, const char* szPath, const char* szName); // appends a filename to the specified path
signed int GetKeyIndex(const char** ppKeys, const char* szKey, const unsigned int len); // gets the index of a string that matches a given string
char* IRC_ReadFile(const char* szPath); // reads a file, without streaming, and returns a pointer to the string (only to be used for small files)
char* trim_left(char *szString);
void trim_right(char *szString);
char* trim(char* szString);
char* replace_first(char* szString, const char cChr, const char cReplacement);
char* IRC_GetParameterAt(const char* szLine, unsigned int iNum);
bool IRC_IsAuthorized(const char *pAddress);

THREAD_CALLBACK system_print(void* lpParam);

#endif // UTILS_H_INCLUDED
