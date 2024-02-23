
#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>

#define PORT 8010
#define MAX_LINE 10000

void function(int client_sock)
{
  struct addrinfo server_conn_addr,*result;

  char buffer[MAX_LINE];
  ssize_t r;
  if ((r = recv(client_sock, buffer, MAX_LINE,0)) > 0)
  printf("request Received: \n\n%s\n", buffer);
  char *ge= strstr(buffer, "GET");
  if(ge != NULL)
  {
    return;
  }
  char *po= strstr(buffer, "POST") ;
  if(po!= NULL)
  {
    return;
  }
  if(strstr(buffer,"mozilla")!=NULL) return;
  char *conn = strstr(buffer, "CONNECT");
  char host_addr[1000];
  char host_port[7];
  //printf("ajhw" );
  if (conn != NULL)
  {
     char *host_start = buffer + strlen("CONNECT") + 1;
     char *host_end = strstr(host_start, " ");
     //printf("Im here 1\n" );

     if (host_end != NULL)
     {

       //printf("IM 2");
         strncpy(host_addr, host_start, host_end - host_start);
         host_addr[host_end - host_start] = '\0';
         char *port_str = strchr(host_addr, ':');
         if (port_str != NULL)
        {
             strcpy(host_port, port_str + 1);
             *port_str = '\0';
         }
         else
         {
             strcpy(host_port, "443");
         }
         printf("Host: %s\n", host_addr);
         printf("Port: %s\n", host_port);
     }
  }
  int n;
  if((n = getaddrinfo(host_addr, host_port, &server_conn_addr, &result)) != 0)  // gets address information of the server
  {
    perror("Getaddrinfo error...\n");
    exit(1);
  }
  int server_conn;
  for(struct addrinfo *p = result; p != NULL; p = p-> ai_next)  // to get the perfect address to connect
  {
    server_conn = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if(server_conn < 0)
    {
      perror("Socket creation error...\n");
      printf("\n");
      continue;
    }
     printf("[+]socket created\n\n");
    if(connect(server_conn, p->ai_addr, p->ai_addrlen) < 0)
    {
      close(server_conn);
      perror("Connection error...\n");
      printf("\n");
      continue;
    }
    printf("[+]connection established\n\n");
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)(p->ai_addr))->sin_addr));
    break;
  }
  char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
  send(client_sock, header, strlen(header), 0);  // we send the success message to the browser/client t
  printf("[+]Connected to server\n");
  while (1)
  {
    struct pollfd fds[2];
    fds[0].fd = client_sock;
    fds[0].events = POLLIN;

    fds[1].fd = server_conn;
    fds[1].events = POLLIN;

    int ret = poll(fds, 2, -1);

    if (ret < 0)
    {
          perror("Poll error \n");
          exit(1);
    }

    for (int fd = 0; fd < 2; fd++)
    {
      if (fds[fd].revents & POLLIN)
      {
          char buffer[MAX_LINE];
          ssize_t received;
          if(fd==0)
          {
            recv(client_sock , buffer, sizeof(buffer), 0);
          }
          else
          {
            recv(server_conn, buffer, sizeof(buffer), 0);
          }
          if (received <= 0)
          {
                break;
          }



          if(fd==0)
          {
            send( server_conn, buffer, received, 0);          }
          else
          {
            send(client_sock, buffer, received, 0);
          }

      }
    }
  }

    close(client_sock);
    close(server_conn);

  return;
}



int main()
{
  struct sockaddr_in server, client;
  int server_sock;


  if((server_sock=socket(AF_INET,SOCK_STREAM,0))<0)
  {
    perror("Error in socket");
    exit(0);
  }

  int yes=1;
  //The SO_REUSEADDR option allows a socket to bind to an address that is already in use by another socket.
  // For example, if a server needs to restart after a crash and bind to the same port as the previous instance,
  // using SO_REUSEADDR can prevent the "Address already in use" error without waiting for the OS to release the port.
  if( setsockopt(server_sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT , &yes, sizeof(int))<0)
  {
      printf("setsocket");
      exit(0);
  }

  memset(&server,'\0',sizeof(server));
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr.s_addr=INADDR_ANY;

  //associates a socket with a specific network address and port number on the local machine.
  if(bind(server_sock, (struct sockaddr*)&server,sizeof(server))<0)
  {
    perror("Error in bind");
    exit(0);
  }


  if(listen(server_sock,10)<0)
  {
    perror("Error in listen");
    exit(0);
  }
  int client_sock;
  socklen_t client_len = sizeof(client);
  while(1)
  {

    if((client_sock=accept(server_sock, (struct sockaddr*)&client,&client_len)) == -1)
    {
        perror("Error in accept");
        exit(1);
    }


    pid_t pid;
    if ((pid=fork()) ==-1)
    {
      printf("pid : -1");

        perror("Error in Fork");
        close(client_sock);
        continue;
    }
    else if(pid==0) //child process
    {
      close(server_sock);
      //https://www.google.com/
      function(client_sock);
      exit(1);


    }
    else //parent process
    {
      // printf("pid : 1");
      close(client_sock);
    }
  }
  close(server_sock);
  return 0;
}

