#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

#include "../lib/netfuncts.h"
#include "../lib/genfunct.h"


char *usrh = "usr:"; //for server to parse username from packet
char* username;
int usr_len = 0; //for length of username

int getusername(char* username); //gets username from stdio
int validateusername(char* username, int sockfd); //asks user to input username and loops to validate with server



int main(int argc, char* argv[]){
	username = malloc(sizeof(char) * 16);
	int sockfd;
	struct hostent *host_info;
	struct sockaddr_in target_addr;
	int port;
	char buffer[1024];

	if(argc < 2){
		printf("Usage: %s <hostname>", argv[0]);
		exit(1);
	}


	if((host_info = gethostbyname(argv[1])) == NULL) {
		printf("Couldn't look up %s\n", argv[1]);
		return -1;
	}


	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		printf("Error with creating socket\n");
		return -1;
	}

	target_addr.sin_family = AF_INET;
	target_addr.sin_port = htons(7890);
	target_addr.sin_addr = *((struct in_addr *)host_info->h_addr);
	memset(&(target_addr.sin_zero), '\0', 8); //zero out the rest of the struct

	if(connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1){
		printf("Error in connecting to target server");
		return -1;
	}

	printf("Connected to server.\n");
  validateusername(username, sockfd); //asks user to input username and loops to validate with server

	//thread creation for send and recieve
	pthread_t threads[2]; //only one for each. May be updated for more functions

	//setup args
	struct sendm_arg *send_arg = (struct send_arg*) malloc(sizeof(struct sendm_arg));
	struct recvm_arg *recv_arg = (struct recv_arg*) malloc(sizeof(struct recvm_arg));

	strcpy(send_arg->username, username); //because strings are evil things and dont like normal shit
	send_arg->sockfd   = sockfd;

	recv_arg->sockfd	 = sockfd;

	printf("Setting up threads\n");

	int send_thread = pthread_create(&threads[0], NULL, send_msg, (void *)send_arg);
	int recv_thread = pthread_create(&threads[1], NULL, recv_msg, (void *)recv_arg);
	if(send_thread || recv_thread){
		  printf("\nERROR: return code from pthread create send_thread is %d\n", send_thread);
			printf("ERROR: return code from pthread create recv_thread is %d\n", recv_thread);
			return -1;
		}
	//close(sockfd); this breaks the code, need to keep it out (?)
	while(1);
	return 0;
}


int getusername(char* username){

	int valid_usr = 0;
	do{

		fgets(username, 16, stdin);
		usr_len = strlen(username);
		//printf("length of username:%d\n", usr_len);
		*(username + usr_len -1) = '\0';
		printf("Username: %s, size: %d\n", username, usr_len);
		if((usr_len < 1) || (usr_len > 16)){
			printf("Error: username length invalid. Try again.\n");
		}
		else{ //if valid username, just return
			valid_usr = 1;
			break;
		}
	}while(valid_usr == 0); //ensure only 16 bytes are used for username
	return 0;
}


int validateusername(char* username, int sockfd){
	char buffer[32];
	printf("Enter username:\t(note: max length = 16 characters)\n");
	while(zerobuffer(buffer) != 0);
	getusername(username);
	int usr_valid = 0;
			do{

				strcat(buffer, usrh);
				strncat(buffer, (const char *)username, sizeof(username)-2);
				strncat(buffer, "\r\n", 2);
				send_string(sockfd, buffer); //send username
				zerobuffer(buffer);
				//wait for username to be validated by server
				recv_line(sockfd, buffer);
				printf("%s\n", buffer);

				if(strcmp(buffer, "NACK") == 0){
					printf("Invalid username, try again.\n");

					printf("Enter username:\t(note: max length = 16 characters)\n");
					while(zerobuffer(buffer) != 0);
					getusername(username);
				}
				else{
					usr_valid = 1;
					break;
				}

			}while(!usr_valid);

			printf("Username validated\n");
			return 0; //got username
}
