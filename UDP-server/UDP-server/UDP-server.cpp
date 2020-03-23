// UDP-server.cpp : 定义控制台应用程序的入口点。
// 需要链接ws2_32.dll

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <WinSock2.h>

using namespace std;


int main()
{
	SOCKET RecvSocket;
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

	int sockfd;// fd means file descriptor
	struct sockaddr_in serveraddr, cliaddr;
	const char* SERV_ADDR = "192.168.1.101"; 
	u_short SERV_PORT = 12345;


	sockfd = socket(AF_INET, SOCK_DGRAM, 0);// fd means file descriptor
	//printf("sockfd = %d\n", sockfd); //Result is 288
	
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERV_ADDR); 
	serveraddr.sin_port = htons(SERV_PORT);


	bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	//The buffer for the incoming data
	char SendBuf[] = "copy that";
	int CliAddrSize = sizeof(cliaddr);
	//printf("CliAddrSize = %d \n", CliAddrSize);//test  --  Result is 16
	int iResult;

	printf("Socket Start ...\n");
	//system("pause"); //test
	
	//一收一发
	while (1)
	{
		char RecvBuf[10020] = "\0";
		//blocked, waiting for connection from client
		printf("Waiting for message from Client...	\n");
		iResult = recvfrom(sockfd, RecvBuf, sizeof(RecvBuf), 0, (sockaddr*)& cliaddr, &CliAddrSize);//为什么 serveraddr前要加&
		if (iResult == SOCKET_ERROR)
		{
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		printf("receive message : [%s] ... %s\n", inet_ntoa(cliaddr.sin_addr), RecvBuf);
		
		iResult = sendto(sockfd, SendBuf, sizeof(SendBuf), 0, (sockaddr*)&cliaddr, sizeof(cliaddr));
		if (iResult == SOCKET_ERROR)
		{
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

	}

	iResult = closesocket(RecvSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error %d\n", WSAGetLastError());
		return 1;
	}
	WSACleanup();

	system("pause");
    return 0;
}

