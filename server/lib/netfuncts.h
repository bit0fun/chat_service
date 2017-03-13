#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>




//pthread structs
struct sendm_arg{
	char username[16];
	int sockfd;
};

struct recvm_arg{
	int sockfd;
};

int send_string(int sockfd, unsigned char *buffer);
int recv_line(int sockfd, unsigned char *dest_buffer);
void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr, char *string); //for server to send to client (note: currently broken)
void send_msg(int sockfd, char* buffer);
int recv_msg(int sockfd);
