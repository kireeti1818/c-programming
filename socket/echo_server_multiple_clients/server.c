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

#define PORT 8080
#define MAX_EVENTS 10

int main() 
{
    int server_fd, new_socket, valread;
    struct sockaddr_in server;
    char buffer[1024] = {0};

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(0);
    }

    // Set socket options to allow reusing the address
    int yes = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(int))) 
    {
        perror("setsockopt");
        exit(0);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind the socket to port 
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server))<0) 
    {
        perror("bind failed");
        exit(0);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) < 0) 
    {
        perror("error while listening");
        exit(0);
    }

    struct pollfd fds[MAX_EVENTS];
    // Number of file descriptors being monitored
    int des = 1;
    memset(fds, 0, sizeof(fds));

    // Add server socket to the pollfd structure
    // it is essential for the server application to accept new connections from clients.
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    printf("Waiting for connections...\n");


    int time_wait=3*60*1000;
    socklen_t addrlen = sizeof(server);
    while(1) 
    {
        // Call poll() to wait for events
        int cnt = poll(fds, des, time_wait);
        if (cnt < 0) 
        {
            perror("error in poll");
            exit(0);
        }
        if(cnt==0)
        {
            perror("poll timeout\n");
            exit(0);
        }
        // Check for events on each file descriptor
        for (int i = 0; i < des; i++) 
        {
            if (fds[i].revents & POLLIN) 
            {
                // New incoming connection
                if (fds[i].fd == server_fd) 
                { 
                    if ((new_socket = accept(server_fd, (struct sockaddr *)&server, &addrlen))<0) 
                    {
                        perror("error while accepting...");
                        exit(0);
                    }

                    printf("New connection, socket fd is %d, ip is: %s,\n",new_socket, inet_ntoa(server.sin_addr));

                    // Adding new connection to the pollfd structure
                    fds[des].fd = new_socket;
                    fds[des].events = POLLIN;
                    des++;
                } 
                // Data available to read on an existing connection
                else 
                { 
                    int client_socket = fds[i].fd;
                    valread = read(client_socket, buffer, 1024);
                    // Client disconnected
                    if (valread == 0)
                    { 
                        printf("Client disconnected\n");
                        close(client_socket);
                        // removing file descriptor
                        fds[i].fd = -1; 
                    } 
                    else
                    {
                        time_t cur_time;
                        time(&cur_time);
                        printf("Message recieved : %s at %s\n",buffer,ctime(&cur_time));
                        strcat(buffer," - ");
                        strcat(buffer,ctime(&cur_time));
                        send(fds[i].fd,buffer,strlen(buffer),0);
                        memset(&buffer,'\0',sizeof(buffer));
                    }
                }
            }
        }
    }
    return 0;
}