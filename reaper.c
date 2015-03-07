#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child(int argc, char **argv) {
	execvp(argv[0], argv);
}

void reaper() {
	pid_t pid;
	int status;

	while (1) {
		if (-1 == (pid = wait(&status)))
			break;

		fprintf(stderr, "[reaper] pid %d exited with status == %d\n",
				pid, status);
	}
}

int main(int argc, char **argv) {
	int pid;

	pid = fork();

	switch(pid) {
		case 0: child(argc-1, argv+1);
			break;

		case -1: perror("fork");
			 return 1;
			 break;

		default: reaper();
	}

	return 0;
}


