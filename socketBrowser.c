#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define BSIZE 0x1000

int main(int argc, char *argv[]) {
	char * request = "GET / HTTP/1.1\r\nHost: www.thrillbox.com\r\nConnection: close\r\n\r\n";
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int fd = socket(AF_INET, SOCK_STREAM,0);
	    
	bzero((char *) &serv_addr, sizeof(serv_addr));
	server = gethostbyname("www.thrillbox.com");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(80);
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	
	connect(fd, &serv_addr, sizeof(serv_addr));
	
	send(fd, request, strlen(request), 0);
	
	while(1) {
		char bufer[BSIZE+10];
		int recived = recvfrom(fd, bufer, BSIZE, 0, 0, 0);
		
		if(recived == 0) {
			break;
		}
		
		bufer[recived] = '\0';
		printf ("%s", bufer);
	}
	
	close(fd);
	return 0;
	
}