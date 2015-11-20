#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
	char buf[1024];
	int sock;
	int port = 50000;
	struct sockaddr_in addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return (1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int addrlen = sizeof(addr);
	if(connect(sock, (struct sockaddr *) &addr, addrlen) < 0)
	{
		perror("connect");
		return(1);
	}

	char *mystr = "Hello Server!";
	printf("SEND to Server:\n%s\n", mystr);

	send(sock, "Hello Server!", sizeof("Hello Server!"), 0);
	recv(sock, buf, 1024, 0);

	printf("Received from Server:\n%s\n", buf);

	close(sock);
	return 0;
}


