#include "database.h"
int usr_lookup(char username[16]){
	FILE *userdb = fopen("userdb.txt", "r"); //database for users
	char *tmp_user = malloc(sizeof(char)*16);
	int strcmp_val;
	char* dblog = malloc(sizeof(char)*64);
	//printf("Username received:\t%s\n%d bytes long\n", username, strlen(username));
  sprintf(dblog, "Username received:\t%s, %d bytes long", username, strlen(username));
	write_log("database_log.txt", dblog);


	if(userdb == 0){
		write_log("database_log.txt","Error: Username database not found");
		exit(1);
	}
	else{ //if database was found,
		while(!feof(userdb)){ //and not end of file,
			if(fscanf(userdb, "%s\n", tmp_user)){ //find user header
				//printf("found in database:\t%s\n%d bytes long\n", tmp_user, strlen(tmp_user)+1);
				//printf("username in looking at file: %s\n", username);
				strcmp_val = strcmp(username, tmp_user); //for testing purposes, this is here
				if(strcmp_val == 0){ //if input username is the same as the one in the database, it is valid
					write_log("database_log.txt", "Found user!");
					fclose(userdb);
					return 1;
				}
				else{
					write_log("database_log.txt", "Still searching for user...");
				}
			}

		}
	fclose(userdb);
	write_log("database_log.txt", "Could not find user, invalid name.");
	return 0;
	}
}



int stringcmp(char *str1, char *str2){ //comparing strings because the built in functions don't work
	int str1_len = strlen(str1);
	int str2_len = strlen(str2);

	int max = 0;

	if(str1_len > str2_len){
		max = str1_len;
	}
	else{
		max = str2_len;
	}
	for(int i = 0; i < max; i++){
		if(!(*(str1 + i) == *(str2+i))){
			return 1;
		}
		else{
		}
	}
	return 0;
}
