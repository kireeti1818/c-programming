#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080
#define WEBROOT "./www" // Directory containing HTML files

int main() 
{
    //int server_fd, new_socket, valread;
    char buffer[1024];
    memset(&buffer,'\0',1024);

    //creating socket
    int server_fd;
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0)
    {
        perror("socket");
        exit(0);
    }


    int yes=1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&yes, sizeof(int)) < 0) 
    {
        perror("setsockopt");
        exit(0);
    }

    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);


    // Bind socket to server
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server))<0) 
    {
        perror("bind failed");
        exit(0);
    }

    //make the specified socket a listening socket
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(0);
    }
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len=sizeof(client);

        // accepting incoming connections.
        int acc=accept(server_fd,(struct sockaddr *)&client,&len);
        if(acc<0)
        {
            perror("accept");
            exit(0);
        }

        //recieving http request from the web browser to open certain file 
        recv(acc , buffer, 1024,0);


        // printf("%s\n", buffer);


        char file_name[100];
        sscanf(buffer,"GET /%s",file_name);
        printf("filename - %s\n",file_name);
        

        char file_path[1000];
        sprintf(file_path,"%s/%s",WEBROOT,file_name);
        //printf("%s\n",file_path);

        int fd = open(file_path, O_RDONLY,0);
        char buff[1024];
        int r;


        // if file is present in folder it will return http ok response and sent content of the file to browser
        // else it will return http not found response and sent content of the file_notfound.html conten to browser
        if(fd>=0) 
        {
            char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
            send(acc , header , strlen(header) , 0 );
            while((r=read(fd,buff,1024))>0)
            {
                send(acc,buff,r,0);
            }
            close(fd);
        }
        else
        {
            char header[]="HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:1024\r\n\r\n";
            send(acc , header , strlen(header) , 0 );
            strcpy(file_name,"file_notfound.html");
            sprintf(file_path,"%s/%s",WEBROOT,file_name);
            int fd = open(file_path, O_RDONLY,0);
            while((r=read(fd,buff,1000))>0)
            {
                // printf("%s",buff);
                send(acc,buff,r,0);
            }
            
        }
        close(acc);
    }
    close(server_fd);

    return 0;
}
