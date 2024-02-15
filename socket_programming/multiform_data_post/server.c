#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include<time.h>
#include <ctype.h>
#include <fcntl.h>


#define PORT 8080
#define MAX_LINE 1000
#define WEBROOT "./www"
#define buffer_size 10000

int main()
{
    int socket_fd;
    //creating socket
    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0)
    {
        perror("socket");
        exit(0);
    }
    int yes=1;

	//enable reuse of local addresses
    if( setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT , &yes, sizeof(int))<0)
    {
        perror("setsocket");
        exit(0);
    }

    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

	//associates socket with a specific network address and port number.
    if(bind(socket_fd,(struct sockaddr *)&server, sizeof(server))<0)
    {
        perror("bind");
        exit(0);
    }
	//make the specified socket a listening socket, allowing it to accept incoming connections.
    if(listen(socket_fd,2)<0)
    {
        perror("listen");
        exit(0);
    }
    char buffer[buffer_size];

    struct sockaddr_in client;
    socklen_t len=sizeof(client);


    while(1)
    {
        int acc_fd=accept(socket_fd,(struct  sockaddr *)&client,&len);
        //allowing it to accept incoming connections.
        if(acc_fd<0)
        {
            perror("accept");
            exit(0);
        }
        memset(&buffer,'\0',strlen(buffer));
        recv(acc_fd , buffer, buffer_size,0);

        char * bond= strstr(buffer, "boundary=");
        bond= strstr(bond, "=");
        bond++;
        char boundary[MAX_LINE];
        memset(&boundary,'\0',strlen(boundary));
        int i=0;
        while(*bond!='\r')
        {
          boundary[i++]=*bond;
          bond++;
        }
        // printf("%s\n", boundary);
        bond++;
        bond = strstr(bond, boundary);
        bond = strstr(bond, "name=");
        char name[MAX_LINE];
        memset(&name,'\0',strlen(name));
        int start=0,ind=0;
        while(1)
        {
          if(start==2) break;
          if(start==1)
          {
            name[ind++]=*bond;
          }
          if (*bond=='"') start++;
          bond++;
        }
        name[ind-1]='\0';
        bond = strstr(bond, name);
        char filename[MAX_LINE];
        memset(&filename,'\0',strlen(filename));
        start=0,ind=0;

        while(1)
        {
          if(start==2) break;
          if(start==1)
          {
            filename[ind++]=*bond;
          }
          if (*bond=='"') start++;
          bond++;
        }
        filename[ind-1]='\0';

        bond = strstr(bond, "\r\n\r\n");
        bond=bond+4;
        char *bond1=strstr(bond, boundary);
        bond1=bond1-2;
        char content[MAX_LINE];
        memset(&content,'\0',strlen(content));
        ind=0;
        while(bond!=bond1)
        {
          // printf("%c",*bond++);
          content[ind++] = *bond++;
        }
        content[ind]='\0';
        char file_path[10050];
        sprintf(file_path,"%s/%s",WEBROOT,filename);
        FILE *file=fopen(file_path,"w");
        i=0;
        while(i<strlen(content))
        {
          fputc(content[i++],file);
        }
        fclose(file);
        char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
        send(acc_fd , header , strlen(header) , 0 );
        char reply[]="file sent to server\r\n";
        send(acc_fd,reply,strlen(reply),0);
        close(acc_fd);
        printf("file recieved and stored\n");
    }
    close(socket_fd);
    return 0;
}
