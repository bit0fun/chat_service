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
	printf("Sent string\r\n");
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
	return 0; //couldn't find EOL
}


void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr, char *string){
	unsigned char *ptr, request[1024];
	int fd, length;

	length = recv_line(sockfd, request);
	printf("Got request from %s:%d\n", inet_ntoa(client_addr_ptr->sin_addr), ntohs(client_addr_ptr->sin_port));
	strncat(string, "\r\n", 2);
	send_string(sockfd, string);


}

int zerobuffer(char *buffer){
	int buff_len = sizeof(buffer);
	for(int i = 0; i < buff_len; i++){
		*(buffer+i) = 0;
		if(*(buffer+i) != 0){
			printf("Buffer could not be cleared.\n");
			return -1;
		}
	}
	return 0;
}
