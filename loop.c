//new line
//comment 2015
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "functions.h"



extern int client_socket[50];

int main()
{
	int opt = TRUE;
	long port;
	int master_socket, addrlen, new_socket, client_socket[50], max_clients = 50, activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;
	char buffer[1025];
	fd_set readfds;
	char *message = "Hello! your messge is:\r\n";

	transport(client_socket, max_clients);

	master_socket = errorhandling(master_socket);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if(bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		for(i=PORT; i < 550000; i++)
		{
			address.sin_port = htons(i);
			if(bind(master_socket, (struct sockaddr *) &address, sizeof(address)) == 0)
			{
				port = i;
				
			break;
			}
			printf("Port is %d", i);
		}
	}

	if(listen(master_socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	addrlen = sizeof(address);
	printf("Waiting for connections...\n");


	while(TRUE)
	{
		FD_ZERO(&readfds);
		FD_SET (master_socket, &readfds);
		max_sd = master_socket;
		for(i = 0; i < max_clients; i++)
		{
			sd = client_socket[i];
			if(sd > 0) 
				FD_SET(sd, &readfds);
			if(sd > max_sd) 
				max_sd = sd;
		}
		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if((activity < 0) && (errno != EINTR))
		{
			printf("select error");
		}
		if(FD_ISSET(master_socket, &readfds))
		{
			if((new_socket = accept(master_socket, (struct sockaddr *)
							&address, (socklen_t*) &addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			printf("New connection, socket fd is %d, ip is : %s,		port : %d \n", new_socket,inet_ntoa(address.sin_addr), ntohs(address.sin_port));
			if(send(new_socket, message, strlen(message), 0) !=
								strlen(message))
			{
				perror("send");
			}
			printf("Welcome message sent successfully\n");
		
			for(i=0; i<max_clients; i++)
			{
				if(client_socket[i] == 0)
				{
					client_socket[i] = new_socket;
					printf("Adding to list of sockets as %d\n", i);
					break;
				}
			}
		}
		
		for(i=0; i<max_clients; i++)
		{
			sd = client_socket[i];
			if(FD_ISSET(sd, &readfds))
			{
				if((valread = read(sd, buffer, 1024)) == 0)
				{
					getpeername(sd, (struct sockaddr*) &address,
												(socklen_t*) &addrlen);
					printf("Host disconnected, ip %s, port %d\n",
						inet_ntoa(address.sin_addr), ntohs(address.sin_port));
					close(sd);
					client_socket[i] = 0;
				}
				else
				{
					send(sd, buffer, strlen(buffer), 0);
				}
			}
		}
	}

	return 0;
}
			


