#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fstream>
#include <vector>
using namespace std;

/*
* Forks children and lets them perform their tasks
* @param urls - the URLs to download
* @param url_counter - total amount of urls
*/
void create_children_parallel(vector<string>& urls, int& url_counter)
{
	/* The process id */
	pid_t pid;

	/* parallel */

	/* serial */
	/* Go through all t Make sure the fork was a success URLs */
	for (vector<string>::iterator urlIt = urls.begin(); urlIt != urls.end(); ++urlIt) {
		/* Create a child */
		pid = fork();

		/* */
		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		/* The child code */
		if (pid == 0) {
			fclose(stdout);
			fclose(stderr);
			
			/* Deploy wget */
			if (execlp("/usr/bin/wget", "child", urlIt->c_str(), NULL) < 0) {
				perror("execlp");
				exit(1);
			}
		}
	}
}


/*
* Read the URLs from the file
* @param urls - the URLs to download
* @param url_counter - total amount of urls
*/

void readUrls(vector<string>& urls, int& url_counter) {
	/* Open the file */
	ifstream urlFile("urls.txt");
	/* The URL buffer */
	string urlBuffer;

	/* Make sure the file can be opened */
	if (!urlFile.is_open()) {
		fprintf(stderr, "Failed to open the file");
		exit(1);
	}

	/* Read the entire file */
	while (!urlFile.eof()) {
		/* Read the buffer */
		urlFile >> urlBuffer;

		/* Push each url into urls vector */
		if (!urlFile.eof()) {
			urls.push_back(urlBuffer);
			++url_counter;
		}
	}

	/* Close the file */
	urlFile.close();
}

int main() {
	/* Read the URL files */
	vector<string> urls;

	/* Counter for total amount of URLs */
	int url_counter = 0;

	/* Read the URLs */
	readUrls(urls, url_counter);

	/* Create child processes */
	create_children_parallel(urls, url_counter);

	/* The parent code */
	/* Parent will wait for all children to terminate */
	while (url_counter > 0) {
		wait(NULL);
		--url_counter;
	}

	return 0;
}
