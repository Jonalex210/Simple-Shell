#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LINE	40 /* 40 char per line, per command */

//function declaration
int parse_command(char command[], char *args[]);

//function definition
int main (void) {
	char *args[MAX_LINE/2 + 1]; /* command line has max of 20 arguments */
	int should_run = 1;

	char command[MAX_LINE];
	int command_length = 0;
	
	while (should_run) {
		printf("-> osh> ");
		fflush(stdout);
		fgets(command, MAX_LINE, stdin); //read in user's input
		
		command_length = parse_command(command, args); //tokenize command
	
		///*DEBUG*/printf("-> [DEBUG: E] command_length: %d\n", command_length);
		///*DEBUG*/printf("-> [DEBUG: F] arg0: %s\n", args[0]);
		///*DEBUG*/printf("-> [DEBUG: G] strcmp: %d\n", strcmp(args[0], "exit"));

		if (command_length == 0) { //an empty command was entered by the user.
			continue; //proceed to reading another command from the user.
		}

		if (strcmp(args[0], "exit") == 0 ){ //user entered exit command to quit simpleShell.
			break; //stop reading anymore commands from user.
		}
		
		pid_t pid = fork(); int status;
			
		if (pid == -1) { //failed to fork().
		//	/*DEBUG*/printf("-> [DEBUG: Failed fork] pid: %d\n", pid);
			perror("-> [ERROR]");
			//exit(1);
		}
		else if (pid == 0 ) { //child process.
		//	/*DEBUG*/printf("-> [DEBUG: Child process] pid: %d\n", pid);
			if (execvp(args[0], args) == -1) {
				perror("-> [ERROR]");
			}
			exit(EXIT_FAILURE);
		}
		else { //parent process. ref: https://wwww.brennan.io/2015/01/16/write-a-shell-in-c
			do {//Loop untill child exits normally
				//wait(&status);
				waitpid(pid, &status, WUNTRACED); //To reap a specific child process compared to the wait() which reaps any arbitrary child.
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		//	/*DEBUG*/printf("-> [DEBUG: Parent Process] pid: %d\n", pid);
		}

		/**
		* After parsing user input, the steps are:
		* (1) fork a child process
		* (2) the child process will invoke execvp()
		* (3) the parent will wait for the child to exit
		*/		
	}
	return 0;
}

int parse_command (char command[], char *args[]) {
	char *token;
	int idx = 0; //Index. reflects the command length at the end of the tokenization.
	char delim[10] = " \t\r\n\a"; //Delimiters.
	
	token = strtok(command, delim);
	while (token != NULL) {
		///*DEBUG*/ printf("-> [DEBUG: C] token: %s\n", token);
		args[idx] = token;
		idx++;

		token = strtok(NULL, delim);
	}
	args[idx] = NULL;
	return idx;
}
