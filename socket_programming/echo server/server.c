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

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd<0)
	{
		printf("error in socket discriptor\n");
		return 0;
	}
	printf("socket created\n");


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


	int bin =bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	if (bin<0)
	{
		perror("sockaddr");
		exit(0);
	}
	printf("binding port \n");


	int lis=listen(sockfd,1);

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
	int rec;
	rec=recv(acc,buff,1000,0);


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
	close(acc);
	close(sockfd);
	return 0;
}