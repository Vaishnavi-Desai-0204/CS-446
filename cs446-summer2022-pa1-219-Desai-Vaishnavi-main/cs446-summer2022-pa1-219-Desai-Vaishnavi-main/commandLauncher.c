#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_LEN 1024

int launchProcesses (char **argv) {
 
	char user_input[BUFFER_LEN]; //get command line
	fgets (user_input, BUFFER_LEN, stdin);
	size_t length = strlen (user_input);
	  
	if (length == 0){
		return 0;
	}
	 
	if (user_input[length - 1] == '\n') {
	     user_input[length - 1] = '\0'; // replace last char by '\0' if it is new line char
	}
	 
	char *token;   //split command using spaces
	token = strtok (user_input, " ");  
	int argc = 0;  
	if (token == NULL){
	    return 0;
	}
	  
	while (token != NULL){     
		argv[argc] = token;
		token = strtok (NULL, " ");
		argc++;   
	}
	argv[argc] = NULL;
	 
	pid_t pid; 
	if (strcmp (argv[0], "cd") == 0){	     
		if (argv[1] == NULL){	 
			perror ("The following error occured: ");
		}		   
		else{
			if (chdir (argv[1]) != 0){
				perror ("The following error occured: ");
			}
		}
	}
	 
	else if (strcmp (argv[0], "exit") == 0){
	 	exit(0);
	}
	 
	else    {
		pid = fork (); // create child process
		if (pid == 0){
			if (execvp (argv[0], argv) == -1){
				perror ("The following error occured: ");
				exit(1);
			}
			return 0;
		}
		     
		else if (pid < 0){
			perror("fork failed!");
			return 1;
		}
		else{
			// parent waits until the child process is done
			wait(NULL);
		}
	}
}
 
int main (int argc, char *argv[]){
	int status;
	while (1){     
		printf ("$> "); // Greeting shell during startup              
		status = launchProcesses (argv);
	}
	return status;
}



