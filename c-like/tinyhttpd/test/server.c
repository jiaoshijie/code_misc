#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	// 定义socket套接字
	// 声明服务端使用的变量
	int server_sock = -1;
	struct sockaddr_in server_addr;
	int server_port = 0;
	// 声明客户端的变量
	int client_sock = -1;
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);
	char buf[1024] = { 0 };
	int buf_len = 0;

	printf("请输入端口号:");
	scanf("%d", &server_port);

	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(server_port);
	server_addr.sin_family = PF_INET;

	bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	listen(server_sock, 5);

	printf("开始监听端口!!!!");
	
	while(1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);

		buf_len = recv(client_sock, &buf, 1023, 0);
		buf[buf_len] = 0;
		printf("buf:%s\n", buf);
		
	}

	return 0;
}
