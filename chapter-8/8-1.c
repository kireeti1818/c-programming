#include<stdio.h>
#include<stdarg.h>
#include<fcntl.h>
#include <unistd.h>
#define buf_size 100
int main(int argc, char * argv[])
{
	char buf[buf_size];
	int fd,fd1;
	fd=open("abc.txt",O_RDONLY,0);
	// fd1=open("stdout",O_WRONLY,0);
	int n;
	while((n=read(fd,buf,buf_size))>0)
	{
		write(STDOUT_FILENO,buf,n);
	}
	
	return 0;
}