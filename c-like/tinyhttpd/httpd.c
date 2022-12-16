#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

// 判断字符是否为空格
#define ISspace(x) isspace((int)(x))
#define SERVER_STRING "Server: jsjhttpd/0.1.0\r\n"

int startup(unsigned short *port);
void error_die(const char* string);
void accept_request(const int sock);
int get_line(const int sock, char* buf, int size);
void unimplemented(const int sock);
void not_found_file(int sock);
void serve_file(int sock, const char *path);
void execute_cgi(int sock, const char *path, const char *method, const char *query_string);
void bad_request(int sock);
void cannot_execute(int sock);

int main(void)
{
  int server_sock = -1;
  unsigned short port = 0;
  int client_sock = -1;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);

  server_sock = startup(&port);

  printf("port: %d\n", port);

  while(1)
  {
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
    if(client_sock == -1)
      error_die("accept() error!");

    accept_request(client_sock);
  }

  close(server_sock);
  return 0;
}

int startup(unsigned short *port)
{
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;

  if(sock == -1)
    error_die("socket() error");

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;

  if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)))
    error_die("bind() error!");

  if(*port == 0)
  {
    socklen_t addr_len = sizeof(addr);
    if(getsockname(sock, (struct sockaddr*)&addr, &addr_len))
      error_die("getsockname() error!");
    *port = ntohs(addr.sin_port);
  }

  if(listen(sock, 5))
    error_die("listen() error!");

  return sock;
}

void error_die(const char* string)
{
  perror(string);
  exit(1);
}

void accept_request(const int sock)
{
  char buf[1024];
  char url[256];
  char path[512];
  int numchars = 0;
  size_t i, j;
  char method[255] = { 0 };
  char *query_string = NULL;
  int cgi = 0;
  struct stat st;

  numchars = get_line(sock, buf, 1024);
  i = j = 0;
  while(!ISspace(buf[j]) && (j < sizeof(buf)) && (i < sizeof(method) - 1))
    method[i++] = buf[j++];
  method[i] = '\0';
  if(strcasecmp(method, "GET") && strcasecmp(method, "POST"))
  {
    unimplemented(sock);
    return;
  }

  while(ISspace(buf[j]) && (j < sizeof(buf) - 1))
    j++;

  i = 0;
  while(!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
    url[i++] = buf[j++];
  url[i] = '\0';

  /** printf("%s\n", url); */
  if(strcasecmp(url, "GET") == 0)
  {
    query_string = url;
    while((*query_string != '?') && (*query_string != '\0'))
      query_string++;
    if(*query_string == '?')
    {
      cgi = 1;
      *query_string = '\0';
      query_string++;
    }
  }

  sprintf(path, "./resources%s", url);
  if(path[strlen(path) - 1] == '/')
    strcat(path, "index.html");

  /** printf("%s\n", path); */
  if(stat(path, &st) == -1)
  {
    // clear buffer
    while((numchars > 0) && strcmp("\n", buf))
      numchars = get_line(sock, buf, sizeof(buf));
    not_found_file(sock);
  }
  else
  {
    if(S_ISDIR(st.st_mode))
      strcat(path, "index.html");
    if((st.st_mode & S_IXUSR) && (st.st_mode & S_IXGRP) && (st.st_mode & S_IXUSR))
      cgi = 1;
    if(cgi)
      execute_cgi(sock, path, method, query_string);
    else
      serve_file(sock, path);
  }
}

int get_line(const int sock, char* buf, int size)
{
  char ch = '\0';
  int i = 0;
  int n;

  while((i < size - 1) && (ch != '\n'))
  {
    n = recv(sock, &ch, 1, 0);
    if(n > 0)
    {
      if(ch == '\r')
      {
        n = recv(sock, &ch, 1, MSG_PEEK);
        if((n > 0) && (ch == '\n'))
          recv(sock, &ch, 1, 0);
        else
          ch = '\n';
      }
    }
    else
      ch = '\n';
    buf[i++] = ch;
  }
  buf[i] = '\0';
  return i;
}

void unimplemented(const int sock)
{
  char buf[1024];
  char path[512] = "./resources/501.html";
  FILE *file;

  sprintf(buf, "HTTP/1.1 501 Method Not Implemented\r\n");
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, SERVER_STRING);
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, "Content-Type: text/html\r\n\r\n");
  send(sock, buf, strlen(buf), 0);
  if((file=fopen(path, "r")) == NULL)
    error_die("fopen() error!");
  fgets(buf, sizeof(buf), file);
  while(!feof(file))
  {
    /** printf("%s", buf); */
    send(sock, buf, strlen(buf), 0);
    fgets(buf, 1024, file);
  }
  fclose(file);
}

void not_found_file(int sock)
{
  char buf[1024];
  char path[512] = "./resources/404.html";
  FILE *file;

  sprintf(buf, "HTTP/1.1 404 NOT FOUND\r\n");
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, SERVER_STRING);
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, "Content-Type: text/html\r\n\r\n");
  send(sock, buf, strlen(buf), 0);
  if((file = fopen(path, "r")) == NULL)
    error_die("fopen() error!");
  fgets(buf, sizeof(buf), file);
  while(!feof(file))
  {
    send(sock, buf, strlen(buf), 0);
    fgets(buf, sizeof(buf), file);
  }
  fclose(file);
}

void serve_file(int sock, const char *path)
{
  int numchars = 1;
  char buf[1024] = { 'A', '\0'};
  FILE *file = NULL;

  // clear buffer ?
  while((numchars > 0) && (strcmp(buf, "\n")))
    get_line(sock, buf, sizeof(buf));

  if((file = fopen(path, "r")) == NULL)
    not_found_file(sock);
  else
  {
    sprintf(buf, "HTTP/1.1 200 OK\r\n");
    send(sock, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(sock, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n\r\n");
    send(sock, buf, strlen(buf), 0);
    fgets(buf, sizeof(buf), file);
    while(!feof(file))
    {
      send(sock, buf, strlen(buf), 0);
      fgets(buf, sizeof(buf), file);
    }
  }

  fclose(file);
}

void execute_cgi(int sock, const char *path, const char *method, const char *query_string)
{
  int numchars = 1;
  char buf[1024];
  int Content_Length = -1;

  if(strcasecmp(method, "GET") == 0)
    while((numchars > 0) && strcmp(buf, "\n"))
      get_line(sock, buf, sizeof(buf));
  else // POST get "Content-Length"
  {
    numchars = get_line(sock, buf, sizeof(buf));
    while((numchars > 0) && strcmp(buf, "\n"))
    {
      buf[15] = '\0';
      if(strcasecmp(buf, "Content-Length:") == 0)
        Content_Length = atoi(&(buf[16]));
      numchars = get_line(sock, buf, sizeof(buf));
    }
    if(Content_Length == -1)
    {
      bad_request(sock);
      return;
    }
  }

  sprintf(buf, "HTTP/1.1 200 OK\r\n");
  send(sock, buf, strlen(buf), 0);

  int cgi_input[2];
  int cgi_output[2];
  pipe(cgi_input);
  pipe(cgi_output);

  int ipid = fork();
  if(ipid == 0) // child
  {
    char method_env[255];
    char length_env[255];
    char string[255];
    dup2(cgi_input[0], 0);
    dup2(cgi_output[1], 1);
    close(cgi_input[1]);
    close(cgi_output[0]);
    sprintf(method_env, "REQUEST_METHOD=%s", method);
    putenv(method_env);
    if(strcasecmp(method, "POST") == 0)
    {
      sprintf(length_env, "CONTENT_LENGTH=%d", Content_Length);
      putenv(length_env);
    }
    else
    {
      sprintf(string, "QUERY_STRING=%s", query_string);
      putenv(string);
    }
    execl(path, path, NULL);
  }
  else // parent
  {
    char ch = '\0';
    int status;
    close(cgi_input[0]);
    close(cgi_output[1]);

    if(strcasecmp(method, "POST") == 0)
      for(int i = 0; i < Content_Length; i++)
      {
        recv(sock, &ch, 1, 0);
        write(cgi_input[1], &ch, 1);
      }
    while(read(cgi_output[0], &ch, 1) > 0)
      send(sock, &ch, 1, 0);

    close(cgi_input[1]);
    close(cgi_output[0]);
    waitpid(ipid, &status, 0);
  }

}

void bad_request(int sock)
{
  char path[512] = "./resources/400.html";
  char buf[1024];
  FILE *file;

  sprintf(buf, "HTTP/1.1 400 BAD REQUEST\r\n");
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, SERVER_STRING);
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, "Content-Type: text/html\r\n\r\n");
  send(sock, buf, strlen(buf), 0);
  if((file = fopen(path, "r")) == NULL)
    error_die("fopen() error!");
  fgets(buf, sizeof(buf), file);
  while(!feof(file))
  {
    send(sock, buf, strlen(buf), 0);
    fgets(buf, sizeof(buf), file);
  }

  fclose(file);
}

void cannot_execute(int sock)
{
  char buf[1024];
  char path[512] = "./resources/500.html";
  FILE *file;

  sprintf(buf, "HTTP/1.1 500 Internal Server Error\r\n");
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, SERVER_STRING);
  send(sock, buf, strlen(buf), 0);
  sprintf(buf, "Content-Type: text/html\r\n\r\n");
  send(sock, buf, strlen(buf), 0);
  if((file = fopen(path, "r")) == NULL)
    error_die("fopen() error!");

  fgets(buf, sizeof(buf), file);
  while(!feof(file))
  {
    send(sock, buf, strlen(buf), 0);
    fgets(buf, sizeof(buf), file);
  }
  fclose(file);
}

