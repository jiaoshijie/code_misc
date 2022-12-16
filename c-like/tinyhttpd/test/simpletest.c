#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>
#include <sys/wait.h>

void error_die(const char *str);

int main(void)
{
  int sock;
  struct sockaddr_in server_addr, client_addr;
  unsigned int port = 0;
  int client_sock;
  socklen_t client_addr_len = sizeof(client_addr);
  char buf[1024] = "/Content-Length: 15";
  char url[255];
  int i, j;

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock == -1)
    error_die("socket() error!");

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;

  if(bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    error_die("bind() error!");

  if(port == 0)
  {
    socklen_t addrlen = sizeof(server_addr);
    if(getsockname(sock, (struct sockaddr*)&server_addr, &addrlen) == -1)
      error_die("getsockname() error!");
    port = ntohs(server_addr.sin_port);
  }
  // 需要\n
  printf("runing port = %d", port);

  if(listen(sock, 5) == -1)
    error_die("listen() error!");


  while(1)
  {
    client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
    if(client_sock == -1)
      error_die("accept() error!");

    i = j = 0;
    while((buf[j] != '\0') && (i < sizeof(url) - 1) && (j < strlen(buf)))
    {
      url[i++] = buf[j++];
    }
    url[i] = '\0';
    printf("wenjian: %s\n", url);
  }



  return 0;
}


void error_die(const char *str)
{
  perror(str);
  exit(1);
}
