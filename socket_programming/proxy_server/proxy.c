#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>

#define MAX_LINE 100000
#define SERVER_PORT 18185

int main() {
    int server_sock;
    struct sockaddr_in server_addr, client_addr;
    struct addrinfo server_conn_addr,*result;
    char buffer[MAX_LINE];
    int bytes_received, bytes_sent;

    // Create socket
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error opening socket");
        exit(0);
    }
    int yes=1;
	//enable reuse of local addresses
    if( setsockopt(server_sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT , &yes, sizeof(int))<0)
    {
        printf("setsocket");
        exit(0);
    }
    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind socket to address
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error on binding\n");
        exit(0);
    }

    // Listen for connections
    if (listen(server_sock, 5) < 0)
    {
          printf("Error on listen\n");
          exit(0);
    }

    printf("Proxy server is running on port %d...\n", SERVER_PORT);
    memset(&buffer,'\0',sizeof(buffer));
    char cont[MAX_LINE];
    while (1)
    {
        // Accept incoming connection
        int client_sock;
        socklen_t client_len = sizeof(client_addr);
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len)) < 0)
        {
              printf("Error on accept\n");
              exit(0);
        }
        // Receive from client
        bytes_received = recv(client_sock, buffer, MAX_LINE, 0);
        if (bytes_received < 0)
        {
                printf("Error receiving from client\n");
                continue;
        }

        else if (bytes_received == 0)
        {
            printf("Connection closed by client\n");
              continue;
        }

        else
        {
            if(strstr(buffer, "CONNECT push.services.mozilla.com:"))
            {
              continue;
            }
            if(strstr(buffer, "detectportal.firefox.com"))
            {
              continue;
            }
            char * ho= strstr(buffer, "Host:");
            char * newline= strstr(ho, "\n");
            long int n =newline-ho-6;

            char host_ip[n];
            sscanf(ho,"Host: %s",host_ip);
            printf("%s \n", host_ip);
            host_ip[n-1]='\0';



            memset(&server_conn_addr, '\0' ,sizeof(server_conn_addr));
        		server_conn_addr.ai_family = AF_UNSPEC; //Allow IPv4 or IPv6
        		server_conn_addr.ai_socktype = SOCK_STREAM;
            int http_port = 80; // HTTP port number

            char port_str[6]={'\0'}; // Assuming port number won't exceed 5 digits
            sprintf(port_str, "%d", http_port);
        		if((n = getaddrinfo(host_ip, port_str, &server_conn_addr, &result)) != 0)  // gets address information of the server
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

            int send_n=send(server_conn,buffer,strlen(buffer),0);
            if(send_n<0)
            {
              printf("missed some bits\n");
              exit(0);
            }
            printf("[+]message sent\n\n");
            printf("%s\n", buffer);

            memset(&cont,'\0',sizeof(cont));
            int rec;

            while((rec = recv(server_conn, cont, MAX_LINE, 0)) > 0)  // receive the response from the server
        		{

        			printf("[+]message recieved\n\n");
              printf("%s\n\n",cont);
              int web_n=send(client_sock,cont,rec,0);
            	if(web_n<0)
            	{
            		printf("missed some bits\n");
            		exit(0);
            	}
        		}

            // }
        }

        close(client_sock);
    }

    close(server_sock);
    return 0;
}
