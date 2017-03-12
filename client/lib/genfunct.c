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
