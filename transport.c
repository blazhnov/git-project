//file transport.c
// new information
// string
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

void transport(int client_socket[], int number_of_clients)
{	
	int i;
	for(i=0; i < number_of_clients; i++)
	{
		client_socket[i] = 0;
	}

}				

