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
	gcc -o server tcpserver.c

clean:
	rm -f server
	rm -f client
