/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: socket.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "socket.h"

int IRC_AttemptConnection(struct server_info* pSI, struct instance_data* pOut)
{
	THANDLE iCoreThread;
	bool bSuccess;

	pOut = malloc(sizeof(struct instance_data));
	pOut->sSI = pSI;

	bSuccess = StartThread(&iCoreThread, IRC_ProcessDataThread, (void*)pOut);
	return bSuccess;
}

static bool InitSocket(struct instance_data* pID, struct addrinfo* aiHints)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
        WSADATA iWsa;
        if (WSAStartup(MAKEWORD(2, 2), &iWsa) != 0)
            return 1;
	#endif

	memset(aiHints, 0, sizeof(aiHints));
	aiHints->ai_family = AF_INET;
	aiHints->ai_socktype = SOCK_STREAM;
	aiHints->ai_protocol = IPPROTO_TCP;

	return (pID->iInstance = socket(aiHints->ai_family, aiHints->ai_socktype, aiHints->ai_protocol)) != INVALID_SOCKET;
}

static bool ResolveAddressFromHostname(struct instance_data* pID, struct sockaddr_in* pSAI, struct addrinfo* aiHints)
{
	struct addrinfo* aiAddrinfoTmp = NULL;
	int iResult = getaddrinfo(pID->cfg(CONFIG_SERVER_ADDRESS), NULL, aiHints, &aiAddrinfoTmp);
	memcpy(pSAI, aiAddrinfoTmp->ai_addr, sizeof(*pSAI));
	freeaddrinfo(aiAddrinfoTmp);
	return !iResult;
}

static bool Connect(struct instance_data* pID, struct sockaddr_in* pSAI)
{
	int iResult;
	pSAI->sin_port = htons(atoi(pID->cfg(CONFIG_SERVER_PORT)));
	iResult = connect(pID->iInstance, (struct sockaddr*)pSAI, sizeof(*pSAI));
	return !iResult;
}

static void SocketCleanup(struct instance_data* pID)
{
	closesocket(pID->iInstance);
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
		WSACleanup();
	#endif
}

static void Reconnect(struct instance_data* pID)
{
    SocketCleanup(pID);
    IRC_EchoEx(pID, '2', "* Reconnecting...");
    ThreadSleep(atoi(g_sCI.pData[CONFIG_BOT_RECONINTERVAL])*1000);
}

void CloseConnection(struct instance_data* pID)
{
	if(pID->iInstance)
	{
		closesocket(pID->iInstance);
		pID->iInstance = 0;
	}
}

THREAD_CALLBACK IRC_ProcessDataThread(void* lpParam)
{
    signed int iRecvSize;
    char szBuffer[513], szLines[1024], *lastLine, *pLine, *pNextLine;
	struct instance_data* pID = (struct instance_data*)lpParam;
	struct sockaddr_in iServices;
	struct addrinfo aiHints;

	while(true)
	{
		if(InitSocket(pID, &aiHints))
		{
			if(ResolveAddressFromHostname(pID, &iServices, &aiHints))
			{
				if(Connect(pID, &iServices))
				{
					szLines[0] = 0;

					IRC_EchoEx(pID, '2', "* Connected to %s:%s", pID->cfg(CONFIG_SERVER_ADDRESS), pID->cfg(CONFIG_SERVER_PORT));

					IRC_SendRawEx(pID, "NICK %s", pID->cfg(CONFIG_SERVER_NICK));
					IRC_SendRawEx(pID, "USER %s * * :%s", pID->cfg(CONFIG_SERVER_USER), pID->cfg(CONFIG_SERVER_REAL));

					while ((iRecvSize = recv(pID->iInstance, szBuffer, sizeof(szBuffer)-1, 0)) > 0)
					{
						szBuffer[iRecvSize] = '\0';

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
				}
				else
					IRC_EchoEx(pID, '2', "* Could not connect to network.");
			}
			else
                IRC_EchoEx(pID, '2', "* Could not resolve address from hostname.");

            Reconnect(pID);
		}
		else
			error("* Could not initialise sockets.");
	}
    return 0;
}

