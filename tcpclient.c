/*  client.c
 *
 *  Created on: 28-Aug-2015
 *      Author: arnavgoel
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h> //This is added to support hostent()

char buffer[1024];
extern int errno;
//TODO: Close the socket after every system call
int main(int argc, char *argv[]){

	if (argc < 3){
		fprintf(stderr,"Usage %s hostname port\n",argv[0]);
		exit(1);
	}
	int sock_fd,ret_err,portno;
	size_t nbytes;
	struct sockaddr_in serveraddr;
	struct hostent *server;//This is a pointer to a D/S that contains IP address of the server I wish to connect to
	server = (struct hostent *)malloc(sizeof(struct hostent));
	char *msg = NULL;
	socklen_t serveraddrlen = (socklen_t)(sizeof(serveraddr));
	memset((void *)&(serveraddr),0,(size_t)serveraddrlen);
	memset((void *)buffer,'\0',sizeof(buffer));
	memset((void *)server,0,sizeof(struct hostent));
	portno = atoi(argv[2]);
	//Create a TCP Socket
	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		fprintf(stderr,"Error %d: Cannot create a STREAM socket\n",errno);
		exit(sock_fd);
	}
	//Get host details
	server = gethostbyname(argv[1]);
	//Assign the different parameters of the serveraddr structure such as IP address, port #, etc
	serveraddr.sin_family = AF_INET;//Internet Family
	serveraddr.sin_port = htons(portno);//Host byte order -> network byte order
	strncpy((char *)&serveraddr.sin_addr.s_addr,
			(char *)server->h_addr,server->h_length);
	if((ret_err = connect(sock_fd,(struct sockaddr *)&serveraddr,serveraddrlen)) < 0){
		fprintf(stderr,"Error %d: Cannot establish a connection from this socket\n",errno);
		exit(ret_err);
	}
	//Send a message !
	fprintf(stdout,"Please Enter the message:\n");
	fgets(buffer,255,stdin);
	buffer[strlen(buffer)-1]='\0';
	msg = buffer;
	if((nbytes = send(sock_fd,msg,strlen(msg),0)) <= 0)
	{
		fprintf(stderr,"Error %d: Send Failure. Exiting....\n",errno);
		exit((int)nbytes);
	}
	memset(buffer,'\0',sizeof(buffer));
	//Receive a message
	if((nbytes = recv(sock_fd,buffer,255,0)) > 0)
	{
		fprintf(stdout,"Received: %s\n",buffer);
	}
	memset(buffer,'\0',sizeof(buffer));
	close(sock_fd);
	return 0;
}



