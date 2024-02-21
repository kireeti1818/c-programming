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
#define SERVER_PORT 8080

int main() {
    int server_sock;
    struct sockaddr_in server_addr, client_addr;
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
            printf("%s\n", buffer);
            if(strstr(buffer, "CONNECT push.services.mozilla.com:"))
            {
              continue;
            }
            if(strstr(buffer, "favicon"))
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
            printf("%s\n", host_ip);

            struct hostent *host_info;
            host_info = gethostbyname(host_ip);
            if (host_info == NULL) {
                printf("gethostbyname failed: %s\n", hstrerror(h_errno));
                exit(1);
            }
            char **address = host_info->h_addr_list;
            // printf("%s\n",inet_ntoa(*(struct in_addr *)*address) );
            int server_conn = socket(AF_INET, SOCK_STREAM, 0);
            if (server_conn < 0) {
                perror("Error creating socket for server connection");
                exit(1);
            }
            printf("[+]socket created\n");
            struct sockaddr_in server_conn_addr;
          	// assigning members to the variable server
          	memset(&server_conn_addr,'\0',sizeof(server_conn_addr));
          	server_conn_addr.sin_family=AF_INET; //ipv4
            server_conn_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*address));
          	server_conn_addr.sin_port=htons(80);
            printf("%s\n", inet_ntoa(server_conn_addr.sin_addr));

          	//establishing connection
            int con = connect(server_conn, (struct sockaddr*)&server_conn_addr, sizeof(server_conn_addr));
          	if(con<0)
          	{
          		printf("error while creating socket of client\n");
          		exit(0);
          	}
            printf("[+]connection established\n");

            int send_n=send(server_conn,buffer,strlen(buffer),0);
            if(send_n<0)
            {
              printf("missed some bits\n");
              exit(0);
            }
            printf("[+]message sent\n");

            char cont[1000000];
            memset(&cont,'\0',sizeof(cont));
            int rec;
            rec=recv(server_conn,cont,1000000,0);
            // while((rec=recv(server_conn,cont,1000000,0)>0)){
              printf("[+]message recieved\n");
              printf("%s\n\n",cont);
              int web_n=send(client_sock,cont,rec,0);
            	if(web_n<0)
            	{
            		printf("missed some bits\n");
            		exit(0);
            	}
            // }
        }

        close(client_sock);
    }

    close(server_sock);
    return 0;
}
