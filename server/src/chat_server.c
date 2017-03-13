#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../lib/netfuncts.h"
#include "../lib/database.h"
#include "../lib/genfunct.h"

#define PORT 7890

int validate_user(int sockfd, char* username);

int main(int argc, char* argv[]){
	char* username = malloc(sizeof(char)*32);
	int sockfd, new_sockfd; //connection to server
	struct sockaddr_in host_addr, client_addr; //address information
	socklen_t sin_size; //size of socket
	int yes = 1;

	char buffer[1024];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		write_log("server_log.txt", "Error with creating socket");
		return -1;
	}
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){ //for reusing address
		write_log("server_log.txt", "Error with setting up socket option SO_REUSEADDR");
		return -1;
	}

	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr= 0; //autofill with IP; edit: may be causing an issue

	memset(&(host_addr.sin_zero), '\0', 8); //zero the rest of the struct, padding?

	if(bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1){
		write_log("server_log.txt", "Error with binding to socket (host)");
		return -1;
	}

	if(listen(sockfd, 5) == -1){
		write_log("server_log.txt", "Error with listening to socket");
		return -1;
	}

	char *tmp = malloc(sizeof(char)*128);
	while(1){

		sin_size = sizeof(struct sockaddr_in);
		new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
		if(new_sockfd == -1){
			write_log("server_log.txt", "Error with accepting connection");
			return -1;
		}
		sprintf(tmp, "Server: got connection from %s, port %d \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		write_log("server_log.txt", tmp);
		//recv_length = recv(new_sockfd, &buffer, 1024, 0);
		int invusr = validate_user(new_sockfd, username);

		if(invusr < 0){ //if too many invalid attempts, close connection
			close(new_sockfd);
		}
		else{
			write_log("server_log.txt", "Validated username, proceed sent.");
		}

		while(recv_msg(new_sockfd)); //gets messages until end of connection
	}

	close(new_sockfd);
	return 0;
}


int validate_user(int sockfd, char* username){
	char buffer[1024];
	int dbvalid_usr = 0;
	int invattempt = 0;
	int usr_validated = 0;
	int recv_length;
	char* tmp = malloc(sizeof(char)*64);
	do{
		while(zerobuffer(buffer) != 0);
		recv_length = recv_line(sockfd, buffer);

		while(!(recv_length > 0));
		sprintf(tmp, "number of tries for user:%d", invattempt);
		write_log("server_log.txt", tmp);

		dbvalid_usr = usr_lookup(buffer);
		if(dbvalid_usr){
			write_log("server_log.txt", "Validated user, sent ACK");
			send_string(sockfd, "ACK\r\n");
			usr_validated = 1;
			break;
		}
		else{
			sprintf(tmp, "Invalid Username:\t%s\n", buffer);
			write_log("server_log.txt", tmp);
			send_string(sockfd, "NACK\r\n");
			usr_validated = 0;
			invattempt++;
		}

	}while(!(usr_validated) && (invattempt < 4)); //while user is invalid and less than 5 invalid attempts
	if(invattempt >= 4){
		return -1;
	}
	else{
		return 0;
	}
}
