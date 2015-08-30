/*  server.c
 *
 *  Created on: 28-Aug-2015
 *      Author: arnavgoel
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <signal.h>
extern int errno;
char buffer[1024];
static int msg_exchg(int newsock_fd);
static void signal_handler(int n);

int main(int argc, char *argv[]){

	if (argc < 2)
	{
		fprintf(stderr,"No port # given\n");
		exit(1);
	}
	int sock_fd,portno,newsock_fd;
	pid_t pid;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	socklen_t serveraddrlen = (socklen_t)(sizeof(serveraddr));
	socklen_t clientaddrlen = (socklen_t)(sizeof(clientaddr));
	memset((void *)&(serveraddr),0,(size_t)serveraddrlen);
	memset((void *)&(clientaddr),0,(size_t)clientaddrlen);
	memset((buffer),'\0',sizeof(buffer));
	portno = atoi(argv[1]);
	size_t nbytes;
	char *pbuff=buffer;
	char *newmsg = "Message Received. Nice to meet you Arnav !";

	if((sock_fd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		fprintf(stderr,"Cannot create a STREAM socket\n");
		exit(sock_fd);
	}
	//Assign the different parameters
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(portno);
	//Only at the server side !

	if((errno = bind(sock_fd,(struct sockaddr *)&serveraddr,serveraddrlen)) < 0){
		fprintf(stderr,"Error %d: Cannot bind the socket\n",errno);
		exit(errno);
	}
	do{
		
		if((nbytes = recvfrom(sock_fd,pbuff,255,0,(struct sockaddr *)&clientaddr,&(clientaddrlen))) > 0)
		{
			fprintf(stdout,"Received: %s\n",pbuff);
		}
		memset(buffer,'\0',sizeof(buffer));
		if((nbytes = sendto(sock_fd,newmsg,strlen(newmsg),0,(struct sockaddr *)&clientaddr,clientaddrlen)) < 0)
		{
			fprintf(stderr,"Error %d: Unable to send new message",errno);
			exit(errno);
		}

	}while(1);
	
	close(sock_fd);
	return 0;

}

/*
void signal_handler(int n){

	wait3(NULL,WNOHANG,NULL);

}
*/
