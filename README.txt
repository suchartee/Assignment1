* =======================================================================
*
* California State University, Fullerton
* CPSC351: Operating System Concept
* Summer 2017: Section 1
* Assignment 1
*
* =======================================================================
* Name: Suchartee (Alice) Kitisopakul, suchartee@csu.fullerton.edu
* Name: Su Win Htet, suhtet@csu.fullerton.edu
* Name: Qiyuan Liu
* =======================================================================
*
* Language used: C++
*
* =======================================================================
* 
* 1) Change directory in terminal to where all files are located
* 2) To build shell program, enter command 'g++ shell.cpp -o shell.out' 
*    To run shell program, enter command 'time ./shell.out'
* 3) To build serial file downloader program, enter command 'g++ serial.cpp -o serial.out' 
*    To run serial program, enter command 'time ./serial.out'
* 4) To build parallel program, enter command 'g++ parallel.cpp -o parallel.out' 
*    To run parallel program, enter command 'time ./parallel.out'
*
* =======================================================================
*
* Execution time for serial downloader
*
*
* Execution time for parallel downloader
*
*
*
* ========================================================================
*
* Extra Questions:
* 1). In the output of time, what is the difference between real, user, and sys times?
*	- Real is the actual running time from start to finish of the call. Or it is a wall clock time.
*	- User is a CPU time running in user-mode (outside of the kernel) within the process.
*	- Sys is a CPU time running in kernel-mode within the kernel. For example, allocating memory or accessing the hardware is counted in this sys time.
*
* 2) Which is longer: user time or sys time? Use your knowledge to explain why.
*	User time is longer. Our code does not ask/request kernel to do anything such as accessing hardware or allocating memory, so the system time is fast.  
*	
* 3) When downloading the files above, which downloader finishes faster? Why? Please Explain.
*	Parallel downloading finishes faster than serial downloading. For serial downloading, the parent cannot create a new child if the current child is not done with the download yet. No matter the size of the file is big or small, the downloader does not care. It just download according to the order of the urls.
*	On the other hand in the parallel downloading, all children are created at once and they start to make a progress on downloading. Parent will wait for any child who finished downloading, and then wait for the next child to   
*
* 4) Repeat the experiment for 10 files (any reasonably large-sized les, e.g., 100 MB, will do). Is the downloader in the previous question still faster? If not so, why? Please Explain.
*
*
* ========================================================================
*
* Hard time with this assignment:
* We knew nothing about terminal and command: Solved by learning from tutorial on lynda.com and trying on Titan server.
* We could not see the result of both downloader because files were too big: Solved by trying with some smaller files
* We did not know what fork(), wait() and execlp() do: We looked through sample code along with the book for more explanation
*
* ========================================================================
