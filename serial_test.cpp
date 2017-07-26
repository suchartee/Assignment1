/* 
* ==============================================================================
*     Authors:		Suchartee (Alice) Kitisopakul, Su Win Htet, Qiyuan Liu
*     Date:   		25 July 2017
*     File name:  	serial.cpp
*     Description: 	This serial file downloader is a program used for 
*       		downloading multiple files from the Internet one by one.   
*       		The program uses fork() and execlp("wget") commands.
* 			The program reads urls.txt containing url file download 
*			links as a commandline, and perform the downloading tasks. 
* ==============================================================================
*/
#include <unistd.h>

#include <sys/types.h>

#include <stdio.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <fstream>

#include <vector>


using namespace std;



/* Global variables for link counter */
int link_counter = 0;

/**

* Forks children and lets them perform their tasks

* @param urls - the urls to download

*/

void create_children_serial(vector<string>& urls)
{
	/* The process id */

	pid_t pid;


	/* Make sure the fork was a success URLs */

	for (vector<string>::iterator urlIt = urls.begin(); urlIt != urls.end(); ++urlIt) {

		/* Create a child */

		pid = fork();

		if (pid < 0) {

			perror("fork");

			exit(1);

		}


		/* The child code */

		else if (pid == 0) {

			/* Deploy wget */

			printf("Child is created with PID %d, from parent PID %d\n", getpid(), getppid());
			/* Check if execlp run a success */

			if (execlp("wget", "wget", urlIt->c_str(), NULL) < 0) {

				perror("execlp");

				exit(1);

			}

		}

		else {

			/* Parent waits until a child exits */
			wait(NULL);

			++link_counter;
			printf("File %d is complete!\n", link_counter);

		}

	}

}




/**

* Read the URLs from the file

* @param urls - the URLs to download

*/


void readUrls(vector<string>& urls) {

	/* Open the file */

	ifstream urlFile("urls.txt");
	/* The URL buffer */
	string urlBuffer;


	/* Make sure the file was opened */

	if (!urlFile.is_open()) {

		fprintf(stderr, "Failed to open the file");

		exit(1);

	}


	/* Read the entire file */

	while (!urlFile.eof()) {

		/* Read the buffer */

		urlFile >> urlBuffer;


		/* Push each url into the vector */
		
		if (!urlFile.eof()) {
			
			urls.push_back(urlBuffer);
		
		}	
	}


	/* Close the file */

	urlFile.close();

}



int main() {

	/* Read the URL files */

	vector<string> urls;


	/* Read the URLs */

	readUrls(urls);


	printf("Getting urls\n");
	printf("There are %d links in urls.txt\n", urls.size());
	/* Create child processes */

	create_children_serial(urls);

	/* Successfully downloading */
	printf("Downloading is done\n");

	return 0;

}
