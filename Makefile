<<<<<<< HEAD
# This is MakeFile
tcpall: tcpclient tcpserver
udpall: udpclient udpserver

udpclient: udpclient.c
	gcc -o client udpclient.c
udpserver: udpserver.c
	gcc -o server udpserver.c
tcpclient: tcpclient.c
	gcc -o client tcpclient.c
tcpserver: tcpserver.c
=======
all: client server

client: tcpclient.c
	gcc -o client tcpclient.c


server: tcpserver.c
>>>>>>> 0c986491cdcb3eb2664bb63633daef131dd11203
	gcc -o server tcpserver.c

clean:
	rm -f server
	rm -f client
