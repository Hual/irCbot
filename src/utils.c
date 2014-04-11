/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: utils.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "utils.h"

unsigned int explode(char ***arr_ptr, char *str, const char delimiter)
{
	char *src = str, *end, *dst;
	char **arr;
	unsigned int size = 1, i;

	while ((end = strchr(src, delimiter)) != NULL)
	{
	  ++size;
	  src = end + 1;
	}

	arr = malloc(size * sizeof(char *) + (strlen(str) + 1) * sizeof(char));

	src = str;
	dst = (char *) arr + size * sizeof(char *);
	for (i = 0; i < size; ++i)
	{
		if ((end = strchr(src, delimiter)) == NULL)
		end = src + strlen(src);
		arr[i] = dst;
		strncpy(dst, src, end - src);
		dst[end - src] = '\0';
		dst += end - src + 1;
		src = end + 1;
	}
	*arr_ptr = arr;

	return size;
}

char* GetApplicationPath(char *szMargv0)
{
	char *pAddr;
	if((pAddr = strrchr(szMargv0, '/')) == NULL) // get a pointer to the last instance of a character which is not a windows system directory delimiter
		pAddr = strrchr(szMargv0, '\\'); // get a pointer to the last instance of a character which is a windows system directory delimiter

	szMargv0[((unsigned int)pAddr - (unsigned int)szMargv0) + 1] = 0; // calculate offsets, set the appropriate char to 0 to remove filename
	return szMargv0; // return a pointer to the filename
}

void GetNameFromPath(char *lpOut, const char *szPath, const char *szName)
{
	strcpy(lpOut, szPath); // append path to empty string
	strcat(lpOut, szName); // append file name to path
}

signed int GetKeyIndex(const char** ppKeys, const char* szKey, const unsigned int len)
{
	signed int i = 0;
	do
	{
		if(!strcmp(ppKeys[i], szKey)) // if the keys match, return the index
			return i;
	}
	while(++i < len); // while pointer is valid
	return -1; // no matching keys found
}

char* trim_left(char *szString)
{
	unsigned int i = 0;
	while(isspace(szString[i++]));
	return &szString[i-1];
}

void trim_right(char *szString)
{
	unsigned int i = strlen(szString);
	while(isspace(szString[--i]));
	szString[i+1] = 0;
}

char *trim(char *szString)
{
	trim_right(szString);
	return trim_left(szString);
}

char* replace_first(char* szString, const char cChr, const char cReplacement)
{
	char* pChar = strchr(szString, cChr);
	if(pChar == NULL)
		return NULL;

	*pChar = cReplacement;
	return pChar;
}

THREAD_CALLBACK system_print(void* lpParam)
{
		FILE *pOutput;
		char szLine[476];

		struct system_print_params* params = (struct system_print_params*)lpParam;

		pOutput = popen(params->pArgs, "r");

		while(fgets(szLine, 1024, pOutput) != NULL)
			IRC_SendRawEx(params->pID, "PRIVMSG %s :%s", params->pChannel, szLine);

		pclose(pOutput);
		free(params->pArgs);
		free(params->pChannel);
		free(lpParam);
		return 0;
}

void error(const char* szString, ...)
{
	va_list pArgs;
    va_start(pArgs, szString);
    vfprintf(stderr, szString, pArgs);
    va_end(pArgs);
}
