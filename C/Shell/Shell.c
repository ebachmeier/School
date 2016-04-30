/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * Janurary 20, 2016
 *
 * To compile and run:
 * 		$ make
 *		$ ./ebachme_a1
 *
 * Shell.c is the main file containing the command prompts and input tokenizing methods.
 *
 * This is a very simplified bash shell written to get experience using fork(), execvp(), 
 * pipe(), dup2(), and signal() system functions.
 *
 * The shell supports command types such as redirection with < > or piping of output.
 *
 * The Example Code from the assignment sheet was used to help me tokenize the commands.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h> /* int open(const char *path, int oflag, ... ) */
#include <sys/stat.h>
#include "StringArray.h"

// the total number of command line arguments allowed
#define MAX_ARGS 10

// the total number of commands per line
#define MAX_COMMANDS 30

// maximum length of the stored history
#define MAX_HISTORY 50

/*
 * makeOperandsList method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method tokenizes an entire command
 * Input Parameters:
 * 		buf - the user input
 *		tokens - list of tokenized commands
 * Output: the number of commands in the list
 */
int makeOperandsList(char *buf, char *tokens[]) {

    char *line;
    int i = 0;
    
    line = buf;
    
    tokens[i] = strtok(line, "<>|");
    
    do {
        i++;
        line = NULL;
        tokens[i] = strtok(line, "<>|");
    } while (tokens[i] != NULL);

    return i;
}

/*
 * tokenizeOperandString method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method tokenizes an operand string
 * Input Parameters:
 * 		buf - the operand to be tokenized
 * Output: the list of arguments
 */
char** tokenizeOperandsString(char* buf) {

    char** tokens = malloc(sizeof(char*) * MAX_ARGS);
    char* line = buf;
    int i = 0;
    
    tokens[i] = strtok(line, " \t\r\n");

    do {
        i++;
        line = NULL;
        tokens[i] = strtok(line, " \t\r\n");
    } while (tokens[i] != NULL);

    return tokens;
}

/*
 * makeOperatorsList method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method adds the operators into their own list in order of appearance
 * Input Parameters:
 * 		buf - the user input string
 *		operator - list to be populated with the operators
 * Output: the number of operators
 */
int makeOperatorsList(char* buf, char* operator) {

    if (buf[0] == '\0') return 0;
    int i = 0;
    int j = 0;
    
    do {
        if (strchr("<>|", buf[i]) != NULL) {
            operator[j++] = buf[i];
        }
    } while (buf[++i] != '\0');
    
    return j;
}

/*
 * executeNextCommand method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method gets the next command in sequence to be executed
 * Input Parameters:
 * 		operand - the list of operands that have been tokenized
 *		tokens - the position to index in the array of elements
 * Output: None
 */
void executeNextCommand(StringArray* operand, int i) {

    char** cmd = getStringArrayElement(operand, i/2);
    
    execvp(cmd[0], cmd);

    printf("Error: Statement '%s' could not be executed\n", cmd[0]);
    
    exit(EXIT_FAILURE);
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: January 20, 2016
 * Purpose: This is the main method for running the shell
 * Input Parameters: None
 * Output: Menu prompt to the console for the user's commands
 */
int main(void) {

    // store all previous command to the string queue qHist
    StringQueue* qHist = initializeStringQueue(MAX_HISTORY);
    
      printf("  _____     _       ______            _                    _            \n");         
	  printf(" |  ___|   (_)      | ___ \\          | |                  (_)          \n");          
	  printf(" | |__ _ __ _  ___  | |_/ / __ _  ___| |__  _ __ ___   ___ _  ___ _ __  \n"); 
	  printf(" |  __| '__| |/ __| | ___ \\/ _` |/ __| '_ \\| '_ ` _ \\ / _ \\ |/ _ \\ '__|\n"); 
	  printf(" | |__| |  | | (__  | |_/ / (_| | (__| | | | | | | | |  __/ |  __/ |    \n"); 
	  printf(" \\____/_|  |_|\\___| \\____/ \\__,_|\\___|_| |_|_| |_| |_|\\___|_|\\___|_|  \n\n"); 

    while (1) {
    
    	// create a string to hold the user input
        char inputLine[MAX_CHARS];

		// print the command-line prompt with the user's name
        printf("%s> ", getenv("USER"));

        if (fgets(inputLine, MAX_CHARS, stdin) != NULL) {
        
        	// save the users input up to 256 characters to the command history
            enqueueString(qHist, inputLine);

            // check for the first word in the user input to be exit
            if (strstr(inputLine, "exit") == inputLine) {
            
            	// free data from memory that has been used
                freeStringQueueData(qHist);
                free(qHist);

				// exit the program successfully
                exit(EXIT_SUCCESS);
            }
            
            // print the user command history to the console
            else if (strstr(inputLine, "history") == inputLine) {
            
                printf("You have previously used the following commands:\n");

                strtok(inputLine, " \t\r\n");
                char* histLength = strtok(NULL, " \t\r\n");

				// default to show 10 previous commands
                int len = 10;

                if (histLength != NULL)
                    len = atoi(histLength);

				// print the appropriate length of commands to the console
                if (len > 0) printStringQueue(qHist, len);
                else printStringQueue(qHist, 10);
            }
            
            // process user inputted commands
            else {
            
                int status;
				
				// create a child process for the process
                pid_t shellChild = fork();

                if (shellChild == -1) printf("Error: Failed to create new process\n");
                else if (shellChild == 0) {
                
                    int nCommands, nOperators;
                    
                    // create an array to store the character operators
                    char operator[10];
                    
                    // create an array to store up to 30 commands
                    char *commandsList[MAX_COMMANDS];

                    nOperators = makeOperatorsList(inputLine, operator);
                    nCommands = makeOperandsList(inputLine, commandsList);

                    // create a string array that holds a list of commands
                    StringArray* operand = initializeStringArray(10);

                    for (int i = 0; i < nCommands; i++) {
                        char** token = tokenizeOperandsString(commandsList[i]);
                        enqueueStringArray(operand, token);
                    }

					// if it is a single argument, we can go ahead an execute the statement
                    if (nOperators == 0) {
                        char** command = dequeueStringArray(operand);
                        execvp(command[0], command);
                        printf("Error: Statement '%s' could not be executed\n", command[0]);
                    }
                    else {
                        if (operator[0] == '|') {
                        
                            int N = 2 * nOperators;

                            // allocate memory for necessary number of pipe file descriptors
                            int* pipefd = (int*)malloc(sizeof(int) * nOperators * 2);

                            // create all pipes neccesary
                            for (int i = 0; i < nOperators; i++) pipe(pipefd + i * 2);

                            for (int i = 0; i < N + 1; i += 2) {
                            
                                pid_t child = fork();
                                
                                if (child < 0) {
                                    printf("Error: Failed to create new process\n");
                                    exit(EXIT_FAILURE);
                                }
                                else if (child == 0) {
                                    if (i == 0) {
                                    
                                        // redirect the standard output to the current pipe
                                        dup2(pipefd[i+1], STDOUT_FILENO);

										// close all pipes on child end
                                        for (int i = 0; i < N; i++) close(pipefd[i]);

                                        executeNextCommand(operand, i);
                                    }
                                    // check if we are at the last command, no pipe
                                    else if (i == N) {
                                    
                                        // redirect the standard input to the previous pipe before
                                        dup2(pipefd[i-2], STDIN_FILENO);

                                        for (int i = 0; i < N; i++) close(pipefd[i]);

                                        executeNextCommand(operand, i);
                                    }
                                    else {
                                    
                                        dup2(pipefd[i-2], STDIN_FILENO);
                                     	dup2(pipefd[i+1], STDOUT_FILENO);

                                        for (int i = 0; i < N; i++) close(pipefd[i]);

                                        executeNextCommand(operand, i);
                                    }
                                }
                            }

                            for (int i = 0; i < N; i++) close(pipefd[i]);
							
							// wait for all children to terminate
                            for (int i = 0; i < N; i++) wait(&status);
							
							// free any used pipe memory
                            free(pipefd);
                        }
                        
                        // argument is either < or >
                        else {
                        
                            char** cmd;

                            for (int i = 0; i < nOperators; i++) {
                            
                                char** cmd0 = getStringArrayElement(operand, i);
                                char** cmd1 = getStringArrayElement(operand, i+1);

                                if (operator[i] == '<') {
                                
                                	// open file to read from
                                    int fd = open(cmd1[0], O_RDONLY);
                                    
                                    // redirect standard output to the file
                                    dup2(fd, STDIN_FILENO);
                                    
                                    // close the file descriptor
                                    close(fd);
                                    
                                    // assign the command
                                    cmd = cmd0;
                                }
                                if (operator[i] == '>') {
                                
                                    // open the file to write to
                                    int fd = open(cmd1[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                                    
                                    // redirect the standard output to the file
                                    dup2(fd, STDOUT_FILENO);
                                    
                                    close(fd);
                                    
                                    if (i == 0) cmd = cmd0;
                                }
                            }

                            pid_t child = fork();
                            
                            if (child < 0) {
                                printf("Error: Failed to create new process\n");
                                exit(EXIT_FAILURE);
                            }
                            else if (child == 0) {
                            
                                execvp(cmd[0], cmd);

                                printf("Error: Statement '%s' could not be executed\n", cmd[0]);
                                exit(EXIT_FAILURE);
                            }
                            wait(NULL);
                        }
                    }

					// free memory used for the command
                    freeStringArrayData(operand);
                    free(operand);
                    exit(EXIT_SUCCESS);
                }
                // parent process
                else {
                    // wait for the child process to terminate before prompting the user again
                    wait(NULL);
                }
            }
        }
        else {
        	printf("Error: Command not found\n");
        }
    }
}
