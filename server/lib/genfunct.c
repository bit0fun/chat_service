#include "genfunct.h"



//write to log file
int write_log(char *log_file, char *string){
	FILE *logfd = fopen(log_file, "a");
	if(logfd == 0){
		printf("Couldn't open file\n");
		exit(1);
	}
	else{
		fprintf(logfd, "%s\n", string);
		fclose(logfd);
	}

	return 0;
}

//zeros buffer, self explanitory
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

char** parse_msg(char* in_buffer){
	char** tokenstr;
	char* tok = in_buffer;
	int counter = 0;
		while((tok = strtok(tok, " ")) != NULL){ //split everything up into a string array
			sprintf(*(tokenstr+counter), "%s", tok);
			counter++;
		}
		sprintf(*(tokenstr+counter+1), NULL);
		return tokenstr; //return the string array

}

int msg_funct_search(char* in_buffer, char* start_tag, char* end_tag){
	char** tokens = parse_msg(in_buffer);

	int ntok = -1;
	int start_pos = 0;
	int end_pos =
	while(tokens[++ntok] != NULL);//gets number of elements in array of strings
	//finding start position
	for (int i = 0; i < ntok; i++) {
		if(strcmp(start_tag, *(tokens + i)) == 0){
			start_pos = i;
			break; //found start
		}
	}
	if(start_pos == 0){
		return -1; //nothing found
	}


	if(end_tag != NULL){
		for (int i = 0; i < ntok; i++) {
			if(strcmp(end_tag, *(tokens + i))){
				end_pos = i;
				break; //found end
			}
		}
		return end_pos; //return position in token array
	}
	else{
		return 0; //found start, but no end needed
	}

}

void funct_msg_handle(functs_t functtype , permission_t pem, char** in_buffer){
	functs_t funct;
	int funct_condition = msg_funct_search(in_buffer, COMMAND_TAG, NULL);
	switch(funct_condition){
		case -1:
			break; //no function found
		case 0:
			funct = command; //found command tag, now to execute command
			exec_funct(funct, );
	}
}

exec_funct(functs_t funct, char* ){

}
