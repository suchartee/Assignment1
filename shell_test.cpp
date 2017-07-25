/* 
* ==============================================================================
*     Authors:		Suchartee (Alice) Kitisopakul, Su Win Htet, Qiyuan Liu
*     Date:   		25 July 2017
*     File name:  	shell.cpp
*     Description: 	This simple shell program prints out the prompt, and 
*       		waits for the user to enter a command such as ls, ps etc.   
*       		The program uses fork() and execlp() commands. The user's
* 			input will be used in execlp() to run an actual linux command
*			The program will terminate once the user's input is exit.
* ==============================================================================
*/
#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <sys/types.h>

#include <stdio.h>

#include <iostream>

#include <string>

using namespace std;



int main()
{

	/* The command buffer */

	string cmdBuff;

	
/* The ID of the child process */

	pid_t pid;

	
/* Keep running until the user has typed "exit" */

	do 
{

		/* Prompt the user to enter the command */

		cerr << "cmd>";

		cin >> cmdBuff;

		
		
		/* If the user wants to exit */

		if(cmdBuff != "exit")
 {

			/* Create a child */

			pid = fork();



			/* Make sure the child was successfully created */

			if (pid < 0)
 {

				perror("fork");

				exit(1);


			}

			/* The child code */

			if (pid == 0) {

				/* Make sure the execlp was a success */

				if (execlp(cmdBuff.c_str(), cmdBuff.c_str(), NULL) < 0) {

					perror("execlp");

					exit(1);

				}

			}


			/* The parent code */

			else {
				/* Wait for the child process to terminate */

				wait(NULL);

			}

		}

	}
 while(cmdBuff != "exit");

	
return 0;	

}
