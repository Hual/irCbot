/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: socket.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "socket.h"

int IRC_AttemptConnection(struct server_info* pSI, struct instance_data* pOut)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
        WSADATA iWsa; // WSA stuff, windows-only
        if (WSAStartup(MAKEWORD(2, 2), &iWsa) != 0)
            return 1;
	#endif

	struct sockaddr_in iServices; // initialize the structures
	struct addrinfo aiHints, *aiAddrinfo = NULL;

	pOut = malloc(sizeof(struct instance_data));
	pOut->sCSI = pSI;

	memset(&aiHints, 0, sizeof(aiHints)); // set aiHints properties
	aiHints.ai_family = AF_INET;
	aiHints.ai_socktype = SOCK_STREAM;
	aiHints.ai_protocol = IPPROTO_TCP;

	if ((pOut->iInstance = socket(aiHints.ai_family, aiHints.ai_socktype, aiHints.ai_protocol)) != INVALID_SOCKET) // initialize socket, store in pOut
	{
		getaddrinfo(pSI->pData[CONFIG_SERVER_ADDRESS], NULL, &aiHints, &aiAddrinfo); // resolve IP from hostname
		memcpy(&iServices,aiAddrinfo->ai_addr,sizeof(iServices)); // copy to the sockaddr_in structure
		freeaddrinfo(aiAddrinfo); // free memory

		iServices.sin_port = htons(atoi(pSI->pData[CONFIG_SERVER_PORT])); // set the port

		if (!connect(pOut->iInstance, (struct sockaddr*)&iServices, sizeof (iServices))) // connect to the socket
		{
			THANDLE iCoreThread; // declare a THANDLE
			bool bSuccess = StartThread(&iCoreThread, IRC_ProcessDataThread, (void*)pOut); // start IRC_ProcessDataThread in a new thread
			return bSuccess;
		}
	}

	closesocket(pOut->iInstance); // close the socket
    #if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
        WSACleanup(); // wsa cleanup, windows only
    #endif
    return 0;
}

THREAD_CALLBACK IRC_ProcessDataThread(void* lpParam)
{
    size_t iRecvSize;
    char szBuffer[512], szLines[1024] = {0}, *lastLine, *pLine, *pNextLine;
	struct instance_data* pID = (struct instance_data*)lpParam;

    IRC_SendRawEx(pID, "NICK %s", pID->cfg(CONFIG_SERVER_NICK)); // send the NICK command
    IRC_SendRawEx(pID, "USER %s * * :%s", pID->cfg(CONFIG_SERVER_USER), pID->cfg(CONFIG_SERVER_REAL)); // register with daemon

    while ((iRecvSize = recv(pID->iInstance, szBuffer, sizeof (szBuffer), 0))) // receive stream response, 512 bytes at a time
    {
		szBuffer[iRecvSize] = '\0'; // zero-terminated

		strcat(szLines, szBuffer);
		pLine = szLines;
		lastLine = strrchr(szLines, '\r');
		*lastLine = *(lastLine+1) = 0;

		do
		{
			pNextLine = strchr(pLine, '\r');
			if(pNextLine)
				*pNextLine = *(pNextLine+1) = 0;

			IRC_ProcessEvents(pID, pLine);

			pLine = pNextLine+2;
		}
		while(pNextLine && strlen(pLine));

		strcpy(szLines, lastLine+2);
    }
    closesocket(pID->iInstance);
    return 0;
}

