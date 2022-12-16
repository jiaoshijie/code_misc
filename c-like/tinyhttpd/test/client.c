#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <memory.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	int sock;
	struct sockaddr_in addr;
	int port;
	char buf[] = "wenjianguanlixitong";
	printf("请输入端口号:");
	scanf("%d", &port);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);

	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	
	send(sock, buf, sizeof(buf), 0);

	


	return 0;
}
