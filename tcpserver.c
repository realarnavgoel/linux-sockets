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

	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
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
	//Listening
	listen(sock_fd,5);
	do{
		//Accepting the connection
		if((newsock_fd = accept(sock_fd,(struct sockaddr *)&clientaddr,&clientaddrlen)) < 0){
			fprintf(stderr,"Error %d: Cannot accept a new connection\n",errno);
			exit(errno);
		}
		if((pid = fork()) < 0){
			fprintf(stderr,"Error %d: Cannot fork a new process\n",errno);
			exit(errno);
		}
		if(pid == 0)
		{//child process
			close(sock_fd);
			(void)msg_exchg(newsock_fd);
			exit(0);
		}
		else
		{//parent process
			close(newsock_fd);
<<<<<<< HEAD
		}	
		signal(SIGCHLD,(signal_handler));	
		//close(newsock_fd);
	}while(1);
	
=======
		}
		signal(SIGCHLD,signal_handler);
		//close(newsock_fd);
	}while(1);

>>>>>>> 0c986491cdcb3eb2664bb63633daef131dd11203
	close(sock_fd);
	return 0;

}

int msg_exchg(int newsock_fd){

	size_t nbytes;
	char *pbuff=buffer;
<<<<<<< HEAD
	char *newmsg = "Message Received. Nice to Meet you, Arnav";
=======
	char *newmsg = "OK, Nice to Meet you";
>>>>>>> 0c986491cdcb3eb2664bb63633daef131dd11203
	if((nbytes = recv(newsock_fd,pbuff,255,0)) > 0)
	{
		fprintf(stdout,"Received: %s\n",pbuff);
	}
	memset(buffer,'\0',sizeof(buffer));
	if((nbytes = send(newsock_fd,newmsg,strlen(newmsg),0)) < 0)
	{
		fprintf(stderr,"Error %d: Unable to send new message",errno);
		exit(errno);
	}

	return 0;
}

void signal_handler(int n){

	wait3(NULL,WNOHANG,NULL);

}
