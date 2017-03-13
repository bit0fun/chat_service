#include "netfuncts.h"
#include <string.h>
int send_string(int sockfd, unsigned char *buffer){
	int sent_bytes, bytes_to_send;
	bytes_to_send = strlen(buffer);
	while(bytes_to_send >0){
		sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
		if(sent_bytes == -1){
			printf("Error in sending string\n");
			return 0; //error in sending
		}
		bytes_to_send -= sent_bytes;
		buffer += sent_bytes;
	}
	zerobuffer(buffer);
	return	1; //for success (?)
}


int recv_line(int sockfd, unsigned char *dest_buffer){
	#define EOL "\r\n" //end of line, carrage return and newline
	#define EOL_SIZE 2
	unsigned char *ptr;
	int eol_matched = 0;


	ptr = dest_buffer;
	while(recv(sockfd, ptr, 1, 0) == 1){//read only 1 byte
		if(*ptr == EOL[eol_matched]) {
			eol_matched++;
			if(eol_matched == EOL_SIZE){		//if all bytes match EOL,
				*(ptr+1-EOL_SIZE) = '\0';	//end the string
				return strlen(dest_buffer);
			}
		}
		else{
			eol_matched = 0;
		}
		ptr++; //increment to next byte
	}
	printf("couldn't find EOL\n");
	while(getchar() != '\n');
	exit(1); //couldn't find EOL
}


void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr, char *string){
	unsigned char *ptr, request[1024];
	int fd, length;

	length = recv_line(sockfd, request);
	printf("Got request from %s:%d\n", inet_ntoa(client_addr_ptr->sin_addr), ntohs(client_addr_ptr->sin_port));
	strncat(string, "\r\n", 2);
	send_string(sockfd, string);


}

//sends message from username to server
void *send_msg(void* args){
	struct sendm_arg* send_arg = (struct sendm_arg*) args;
	int sockfd = send_arg->sockfd;
	char *username = send_arg->username;
	char usr_buff[32];
	char msg[4070];
	char buffer[4096]; //may need to update to incorporate longer messages in the future


	strcat(usr_buff, "usr:");
	strncat(usr_buff, (const char *)username, sizeof(username)-2);

	while(1){

		printf("%s>", usr_buff);
		sprintf(buffer, "%s>", usr_buff);
		fgets(msg, 4070, stdin); //gets the message
		*(msg + strlen(msg) -1) = '\0'; //formats the message properly
		strncat(buffer, msg, strlen(msg));
		strncat(buffer, "\r\n", 2);
		send_string(sockfd, buffer);

	}


}

void *recv_msg(void* args){
	struct recvm_arg* recv_arg = (struct recvm_arg*) args;
	int sockfd = recv_arg->sockfd;
	char title[20];
	char msg[4070];
	char buffer[4096]; //may need to update to incorporate longer messages in the future
	while(1){
		recv_line(sockfd, buffer);
		printf("%s\n", buffer);
	}

}
