// UDP-client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


int main()
{

	SOCKET CliSocket = INVALID_SOCKET;
	WSADATA wsaData;
	int ERRORCODE;

	//初始化Winsock
	ERRORCODE = WSAStartup(MAKEWORD(2, 2), &wsaData); //test MAKEWORD(2, 1)都行？
	if (ERRORCODE != 0)
	{
		printf("WSAStartup failed: %d\n", ERRORCODE);
		WSACleanup();
		return 1;
	}

	//记录IP和端口
	int sockfd;// fd means file descriptor
	struct sockaddr_in serveraddr, cliaddr;
	const char* SERV_ADDR = "192.168.1.101";
	u_short SERV_PORT = 12345;

	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);// fd means file descriptor

	//ip地址和端口记录在 sockaddr_in 中
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	serveraddr.sin_port = htons(SERV_PORT);

	int SERVAddrSize = sizeof(serveraddr);

	printf("Socket Start ...\n");
	printf("Please input message:\n");
	char SendBuf[10020] = "\0";
	char RecvBuf[10020] = "\0";
	//system("pause"); //test

	int iResult;


	//一收一发
	while (1)
	{
		scanf("%s", SendBuf);
		if (strcmp(SendBuf, "bye") == 0)
		{
			printf("bye!");
			Sleep(1000);
			if (iResult == SOCKET_ERROR)
			{
				printf("closesocket failed with error %d\n", WSAGetLastError());
				return 1;
			}
			break;
		}

		printf("sending...\n");
		iResult =sendto(sockfd, SendBuf, sizeof(SendBuf), 0, (sockaddr*)& serveraddr, sizeof(serveraddr));
		if (iResult == SOCKET_ERROR)
		{
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		else
		{
			Sleep(10);
			iResult = recvfrom(sockfd, RecvBuf, sizeof(RecvBuf), 0, (sockaddr*)& serveraddr, &SERVAddrSize);
			if (iResult == SOCKET_ERROR)
			{
				printf("recvfrom failed with error %d\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}
			printf("receive message from server: %s\n", RecvBuf);
		}
	}

	iResult =  closesocket(CliSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error %d\n", WSAGetLastError());
		return 1;
	}
	WSACleanup();

	system("pause");
    return 0;
}

