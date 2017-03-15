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
		while((tok = strtok(tok, search)) != NULL){ //split everything up into a string array
			sprintf(*(tokenstr+counter), "%s", tok);
			counter++;
		}
		sprintf(*(tokenstr+counter+1), NULL);
		return tokenstr; //return the string array

}

int msg_function_handle(char* in_buffer, char* start_tag, char* end_tag, char* replace){
	char** tokens = parse_msg(in_buffer);
	int ntok = -1;
	while(tokens[++ntok] != NULL);//gets number of elements in array of strings
	for (int i = 0; i < ntok; i++) {
		
	}




}
