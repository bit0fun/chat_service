#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_log(char *log_file, char *string); //write to log file
int zerobuffer(char *buffer); //clears buffer
char** parse_msg(char* in_buffer, char* start_tag, char* end_tag, char* replace);
