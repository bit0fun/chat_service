#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	user, //basic functionality
	server, //allows for more commands, not super user though for security reasons
	device //minimal functionality
}permission_t;

typedef enum{
	command, //trying to issue command to chat
	usrdmsg, //sending message to specific user
	style //affects font in chat
}functs_t;

#define COMMAND_TAG "!"
#define USR_DMSG	  "@"


int write_log(char *log_file, char *string); //write to log file
int zerobuffer(char *buffer); //clears buffer
char** parse_msg(char* in_buffer);
int msg_funct_search((char* in_buffer, char* start_tag, char* end_tag, char* replace);
