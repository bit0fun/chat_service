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
