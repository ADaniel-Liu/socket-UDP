# socket-UDP（winsock）

## 1.功能设计

1.   UDP服务端阻塞等待客户端发来数据，接收数据后进行应答，返回发来的数据。
2.   UDP客户端向客户端发送数据，过后接收客户端发来的数据。


## 2.开发环境及工具

1.   IDE: VisualStudio (Version = 15.0.26430.16)
2.   OS:Windows_NT x64


## 3. 实现原理


### 3.1 服务端

  首先使用socket()函数创建套接字，创建WSAData类型变量wsadata。调用WSAStartup(MAKEWORD(2,1), &wsadata)函数启动一个进程。在进行服务端的进程前进行准备工作，包括：
1.	指定协议类型存于sockaddr_in类型变量中
2.	指定协议族存于sockaddr_in类型变量中
3.	制定端口存于sockaddr_in类型变量中
4.	将本机IP地址存于sockaddr_in类型变量中

  完成以上步骤后，创建套接字socket,再用bind()函数绑定套接字。然后用一个不停止循环，循环中recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len)在接受不到客户端数据时处于阻塞状态。接受到服务端后显示收到客户端信息，并使用sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len)将信息传给客户端。
最后使用closesocket(socket1)关闭套接字socket，再使用WSACleanup函数终止使用Winsock 2 DLL。


### 3.2 客户端
  客户端同样首先使用socket()函数创建套接字，创建WSAData类型变量wsadata。调用WSAStartup(MAKEWORD(2,1), &wsadata)函数启动一个进程。在进行服务端的进程前进行准备工作，包括：
1.	指定协议类型存于sockaddr_in类型变量中
2.	指定协议族存于sockaddr_in类型变量中
3.	制定端口存于sockaddr_in类型变量中
4.	将本机IP地址存于sockaddr_in类型变量中

  完成以上步骤后，创建套接字socket,再用bind()函数绑定套接字。然后用一个不停止循环，循环中输入bye能跳出循环，sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len)将信息传给客户端。
最后使用closesocket(socket1)关闭套接字socket，再使用WSACleanup函数终止使用Winsock 2 DLL。


