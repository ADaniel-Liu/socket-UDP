#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Winsock2.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//SOCKET
	SOCKET socket1; //SOCKET ָ���� long long 
	struct WSAData wsadata;//struct WSAData ����д�� WSADATA 

	int iResult = 0; //used to return function results

	iResult = WSAStartup(MAKEWORD(2,1), &wsadata); //& Ϊȡ��ַ�� 
	if(iResult != NO_ERROR) 
	{
		wprintf(L"Error at WSAStartup()\n");
		WSACleanup(); // The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
		return 1;
	} 

	printf("Winsock client start ... \n");

	//׼�� 
	//ip�� 
	const char* ip =  "192.168.43.15";	//����д�������ַ����޷��ı� 
	struct  sockaddr_in server; //sockaddr��sa_data��Ŀ���ַ�Ͷ˿���Ϣ����һ���ˣ�sockaddr_in ��������ȱ��
	int len = sizeof(server);
	server.sin_family = AF_INET; // AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). 
	server.sin_port = htons(12345); //���˿ں��������ֽ���ת��Ϊ�����ֽ��������ֵ(host to net)
	server.sin_addr.s_addr = inet_addr(ip);


	socket1 = socket(AF_INET, SOCK_DGRAM, 0); //s = socket(domain, type, protocol); typeΪSOCK_DGRAM(UDP) �� SOCK_STREAM(TCP) 
    //printf("%d\n",socket1);   //test

	while(1)
	{
		//һ��һ�� ����ѭ��
		char buffer[1024] = "\0"; 

		printf("input message: \n");
		scanf("%s", buffer);
		
		if(strcmp(buffer, "bye") == 0)
		{
			printf("exit, bye!\n");
			Sleep(100);
			closesocket(socket1);
			break;
			
		}

		if(sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, len) != SOCKET_ERROR)
		{
			printf("sending...\n");
			Sleep(100);	
			if(recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) != SOCKET_ERROR)
			{
				printf("recevie message : %s\n", buffer); //The inet_ntoa function converts an (Ipv4) Internet network address into an ASCII string in Internet standard dotted-decimal format.
			}
		}	
	}
	closesocket(socket1);
	WSACleanup();  //��� 
	system("pause");

	return 0;
}















