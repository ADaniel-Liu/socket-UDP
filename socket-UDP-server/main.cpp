#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Winsock2.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//SOCKET
	SOCKET socket1; //SOCKET 指的是 long long 
	struct WSAData wsadata;//struct WSAData 可以写成 WSADATA 

	int iResult = 0; //used to return function results

	iResult = WSAStartup(MAKEWORD(2,1), &wsadata); //& 为取地址符 
	if(iResult != NO_ERROR) 
	{
		wprintf(L"Error at WSAStartup()\n");
		WSACleanup(); // The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
		return 1;
	} 

	printf("Winsock start ... \n");

	//准备 
	//ip绑定 
	const char* ip =  "192.168.43.15";	//这种写法用于字符串无法改变 
	struct  sockaddr_in local; //sockaddr中sa_data把目标地址和端口信息混在一起了，sockaddr_in 解决了这个缺陷
	local.sin_family = AF_INET; // AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). 
	local.sin_port = htons(12345); //将端口号由主机字节序转换为网络字节序的整数值(host to net)
	local.sin_addr.s_addr = inet_addr(ip);

	//这段代码是啥来的？？？	
	struct sockaddr_in client;  
	int len = sizeof(client);

	socket1 = socket(AF_INET, SOCK_DGRAM, 0); //s = socket(domain, type, protocol); type为SOCK_DGRAM(UDP) 和 SOCK_STREAM(TCP) 
    //printf("%d\n",socket1);   //test

	//bind
    iResult = bind(socket1, (struct sockaddr*)&local, sizeof(local));
    //printf("%d\n", iResult);//test
	if(iResult == SOCKET_ERROR)
	{
	wprintf(L"bind failed with error %u\n", WSAGetLastError());
        closesocket(socket1);
        WSACleanup();
        return 1;
	} 

	while(1)
	{
		//一收一发 无限循环
		char buffer[1024] = "\0"; 

		printf("waiting for message from the client...\n");

		if(recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len) != SOCKET_ERROR)
		{
		//	printf("recevie message : [%s] --- %s\n",inet_ntoa(client), buffer);
			printf("recevie message : [%s] --- %s\n",inet_ntoa(client.sin_addr), buffer); //The inet_ntoa function converts an (Ipv4) Internet network address into an ASCII string in Internet standard dotted-decimal format.
			sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len);
		}	
	}
	closesocket(socket1);
	WSACleanup();  //后加 
	system("pause");

	return 0;
}











