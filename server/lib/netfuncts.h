#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

int send_string(int sockfd, unsigned char *buffer);
int recv_line(int sockfd, unsigned char *dest_buffer);
void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr, char *string); //for server to send to client (note: currently broken)
int zerobuffer(char *buffer); //clears buffer
