#define TRUE 1
#define FALSE 0
#define PORT 50000

int client_socket[50];

int errorhandling(int);
void transport(int client_socket[], int number_of_clients);
