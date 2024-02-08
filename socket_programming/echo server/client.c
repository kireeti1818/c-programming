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
	char *server_ip="127.0.0.1";


	//creating socket
	int sockfd= socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("error while creating socket of client\n");
		exit(0);
	}

	// assigning members to the variable server
	struct sockaddr_in server;
	memset(&server,'\0',sizeof(server));
	server.sin_family=AF_INET; //ipv4
	server.sin_addr.s_addr=inet_addr(server_ip);
	server.sin_port=htons(port);


	//establishing connection
	int con=connect(sockfd,(struct sockaddr * ) &server,sizeof(server));
	if(con<0)
	{
		printf("error while creating socket of client\n");

	}


	char msg[1000];
	fgets(msg, sizeof(msg), stdin) != NULL;
	msg[strlen(msg)]='\0';


	//sending message to the server
	int n=send(sockfd,msg,strlen(msg),0);
	if(n<0)
	{
		printf("missed some bits\n");
	}


	char buff[1000];
	memset(&buff,'\0',sizeof(buff));

	//Recieving message from the server
	int rec;
	rec=recv(sockfd,buff,1000,0);
	buff[strlen(buff)-1]='\0';


	// printing the respone along with timestamp
	time_t cur_time;
	time(&cur_time);
	printf("Response recieved from server is :- ( %s ) \nat %s",buff,ctime(&cur_time));
	close(sockfd);
	return 0;
}
