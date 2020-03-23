# socket-UDP（winsock）

## 功能设计

## 开发环境及工具

1.IDE: Visual Studio Code 1.43.1
2.OS:Windows_NT x64

## 1. 实现原理


### 1.1 服务端
  首先使用socket()函数创建套接字，创建WSAData类型变量wsadata。调用WSAStartup(MAKEWORD(2,1), &wsadata)函数启动一个进程。在进行服务端的进程前进行准备工作，包括：
1.	指定协议类型存于sockaddr_in类型变量中
2.	指定协议族存于sockaddr_in类型变量中
3.	制定端口存于sockaddr_in类型变量中
4.	将本机IP地址存于sockaddr_in类型变量中

  完成以上步骤后，创建套接字socket,再用bind()函数绑定套接字。然后用一个不停止循环，循环中recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)在接受不到客户端数据时处于阻塞状态。接受到服务端后显示收到客户端信息，并使用sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len)将信息传给客户端。
最后使用closesocket(socket1)关闭套接字socket，再使用WSACleanup函数终止使用Winsock 2 DLL。


### 1.2 客户端
  客户端同样首先使用socket()函数创建套接字，创建WSAData类型变量wsadata。调用WSAStartup(MAKEWORD(2,1), &wsadata)函数启动一个进程。在进行服务端的进程前进行准备工作，包括：
1.	指定协议类型存于sockaddr_in类型变量中
2.	指定协议族存于sockaddr_in类型变量中
3.	制定端口存于sockaddr_in类型变量中
4.	将本机IP地址存于sockaddr_in类型变量中

  完成以上步骤后，创建套接字socket,再用bind()函数绑定套接字。然后用一个不停止循环，循环中输入bye能跳出循环，sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len)将信息传给客户端。
最后使用closesocket(socket1)关闭套接字socket，再使用WSACleanup函数终止使用Winsock 2 DLL。


