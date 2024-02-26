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

int main()
{
    int socket_fd;
    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0)
    {
        perror("socket");
        exit(0);
    }
    int yes=1;
    if( setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT , &yes, sizeof(int))<0)
    {
        perror("setsocket");
        exit(0);
    }

    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    if(bind(socket_fd,(struct sockaddr *)&server, sizeof(server))<0)
    {
        perror("bind");
        exit(0);
    }

    if(listen(socket_fd,0)<0)
    {
        perror("listen");
        exit(0);
    }
    char buffer[1000];
    memset(&buffer,'\0',strlen(buffer));
    struct sockaddr_in client;
    socklen_t len=sizeof(client);


    while(1)
    {
        int acc_fd=accept(socket_fd,(struct  sockaddr *)&client,&len);
        if(acc_fd<0)
        {
            perror("accept");
            exit(0);
        }
        recv(acc_fd , buffer, 1024,0);
        // printf("%s\n", buffer);
        char line[MAX_LINE];
        char pattern[]="file_name";
        char *ptr =buffer;
        while(sscanf(ptr,"%[^\n]",line)!=EOF)
        {
            ptr=ptr+strlen(line)+1;
            if (strstr(line, pattern) != NULL)
            {
                break;
            }
            if (*ptr == '\0')
                break;
            memset(&line,'\0',strlen(line));
        }
        // printf("%s",line);
        int start=0,end=0;
        for(int i=0;i<strlen(line);i++)
        {
            if(line[i]=='=')
            {
                start=i+1;
            }
            if(line[i]=='.')
            {
                end=i;
            }
        }
        int size = end-start+6;
        char file_name[size];

        for (int i = 0; i < size; i++) 
        {
            file_name[i] = line[start + i];
        }
        file_name[size]='\0';
        printf("FILE REQUESTED :  %s\n", file_name);
        char file_path[MAX_LINE];
        
        sprintf(file_path,"%s/%s",WEBROOT,file_name);
        int fd = open(file_path, O_RDONLY ,0);
        char buff[1024];
        int r;

        if(fd>=0) 
        {
            char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
            send(acc_fd , header , strlen(header) , 0 );
            while((r=read(fd,buff,1024))>0)
            {
                send(acc_fd,buff,r,0);
            }
            close(fd);
        }
        else
        {
            char header[]="HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
            send(acc_fd , header , strlen(header) , 0 );
            strcpy(file_name,"file_notfound.html");
            sprintf(file_path,"%s/%s",WEBROOT,file_name);
            int fd = open(file_path, O_RDONLY,0);
            while((r=read(fd,buff,1000))>0)
            {
                // printf("%s",buff);
                send(acc_fd,buff,r,0);
            }
            
        }
        close(acc_fd);
    }
    close(socket_fd);
    return 0;
}