#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<unistd.h>
#include<time.h>


int main(int argc, char const *argv[])
{
	int port=30233;
	char *address="127.0.0.1";

	//creating socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd<0)
	{
		printf("error in socket discriptor\n");
		return 0;
	}
	printf("socket created\n");

	//enable reuse of local addresses 
	int yes=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
	{
		printf("setsockopt");
		exit(0);
	}


	struct sockaddr_in server,client;
	memset(&server,'\0',sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(address);
	server.sin_port=htons(port);

	//associates socket with a specific network address and port number.
	int bin =bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	if (bin<0)
	{
		perror("sockaddr");
		exit(0);
	}
	printf("binding port \n");

	//make the specified socket a listening socket, allowing it to accept incoming connections.
	//'1' indicates the maximum length of the queue of pending connections
	int lis=listen(sockfd,1);

	//allowing it to accept incoming connections.
	socklen_t len=sizeof(client);
	int acc;
	if ((acc = accept(sockfd, (struct sockaddr *)&client, &len)) < 0)
	{
		printf("error while acceptint");
		return 0;
	}
	printf("accepting the connection\n");


	char buff[1000];
	memset(&buff,'\0',1000);

	//receving message from the server
	int rec;
	rec=recv(acc,buff,1000,0);

	//sending the received message to client as a response by attaching time stamp
	time_t cur_time;
	time(&cur_time);
	printf("Message recieved : %s at %s",buff,ctime(&cur_time));
	strcat(buff," - ");
	strcat(buff,ctime(&cur_time));
	printf("%s",buff);
	int n=send(acc,buff,strlen(buff),0);
	if(n<0)
	{
		printf("error in sending\n");
	}

	//closing the acc and sockfd
	close(acc);
	close(sockfd);
	return 0;
}
